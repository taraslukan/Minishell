/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/15 17:53:15 by fluzi            ###   ########.fr       */
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


void std_exv(t_comand *comand) {
    if (is_builtin(comand->exe)) {
        printf("Builtin\n");
        //execute_builtin(comand); // Funzione per eseguire il builtin (da implementare)
        return;
    }

    if (access(comand->exe, X_OK) != 0) {
        perror("Errore: accesso negato o file inesistente");
        return;
    }

    if (execve(comand->exe, comand->args, environ) == -1) {
        perror("Errore in execve");
        exit(EXIT_FAILURE); // Termina il processo in caso di errore
    }
}
