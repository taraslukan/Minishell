/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/16 15:02:04 by fluzi            ###   ########.fr       */
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

void std_exv(t_comand *comand)
{
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("Errore durante la fork");
        return;
    }

    if (pid == 0) {
        if (is_builtin(comand->exe)) {
            execute_builtin(comand);
            _exit(0); 
        }
        if (access(comand->exe, X_OK) != 0) {
            fprintf(stderr, "Errore: accesso negato o file inesistente\n");
            _exit(127); 
        }
        if (execve(comand->exe, comand->args, comand->core->env) == -1) {
            perror("Errore in execve");
            _exit(126);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}


