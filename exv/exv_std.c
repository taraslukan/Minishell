/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/28 21:55:25 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

void call_exe_func(t_comand *cmd, int *fd) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        if (fd[0] >= 0) close(fd[0]);
        if (fd[1] >= 0) close(fd[1]);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Processo figlio
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        exe_func(cmd, fd);  // Esegui il comando
        exit(EXIT_FAILURE);  // Se execve fallisce, termina il processo figlio
    }

    // Processo padre
    if (fd[1] >= 0) close(fd[1]);  // Chiudi fd[1] nel processo padre
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        if (fd[0] >= 0) close(fd[0]);
        exit(EXIT_FAILURE);
    }
}

// Funzione principale per gestire l'esecuzione dei comandi
void std_exv(t_coreStruct *core) {
    int fd[2] = {-1, -1};  // Inizializza i file descriptor della pipe

    if (!core || core->pipe.number <= 0 || !core->functions) {
        fprintf(stderr, "Invalid core structure\n");
        exit(EXIT_FAILURE);
    }

    if (core->pipe.number > 0 && pipe(fd) < 0) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < core->pipe.number; i++) {
        print_command(&core->functions[i]);

        if (is_builtin(core->functions[i].exe)) {
            execute_builtin(&core->functions[i]);
        } else {
            call_exe_func(&core->functions[i], fd);
        }
    }

    // Chiudi i file descriptor della pipe alla fine
    if (fd[0] >= 0) close(fd[0]);
    if (fd[1] >= 0) close(fd[1]);
}