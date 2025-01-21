/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/21 17:03:38 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

extern char **environ;

void call_exe_func(t_comand *cmd)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        printf("START:: \n");
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        one_fun_std_exe(cmd);
        exit(EXIT_FAILURE); // Should not reach here
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        waitpid(pid, &status, 0);  // Aspetta che il figlio termini

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);  // Estrae il codice di uscita
            printf("Il processo figlio è terminato con codice di uscita: %d\n", exit_code);
        }
    }
    
}

void std_exv(t_coreStruct *core)
{
    size_t i = 0;

    while (i < core->pipe.number)
    {
        printf("Eseguo %zu / %zu\n", i, core->pipe.number);
        if (is_builtin(core->functions[i].exe))
            execute_builtin(&core->functions[i]);
        else
            call_exe_func(&core->functions[i]);
        i++;
    }
}
