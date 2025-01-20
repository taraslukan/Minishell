/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/20 15:13:02 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

extern char **environ;

// void	case_finder(t_coreStruct *core)
// {
// 	if(core->pipe.exists)
// 		pipe_exv(core);
// 	else
// 		std_exv(&core->functions[0]);
// }

// void	pipe_exv(t_coreStruct *core)
// {

// }

// void std_exv(t_comand *comand) {
//     if (is_builtin(comand->exe)) {
//         execute_builtin(comand);
//         return;
//     }

//     if (access(comand->exe, X_OK) != 0) {
//         printf("Errore: accesso negato o file inesistente");
//         return;
//     }

//     if (execve(comand->exe, comand->args, comand->core->env) == -1) {
//         printf("Errore in execve");
// 		return;
//     }
// }

void call_exe_func(t_comand *cmd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        one_fun_std_exe(cmd);
        exit(EXIT_SUCCESS); // Terminare il figlio in modo esplicito
    } else {
        // Siamo nel padre
        int status;
		waitpid(pid, &status, 0);
    }
}

void std_exv(t_comand *cmd)
{
    if (is_builtin(cmd->exe)) {
        execute_builtin(cmd);
    } else {
		printf("std");
        call_exe_func(cmd);
    }
}
