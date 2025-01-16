/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:20 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/16 17:04:12 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"  // Aggiungi questa riga

void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nRicevuto SIGINT (Ctrl+C). Terminato il processo figlio.\n", 58);

    // Uccidi il processo figlio (puoi usare il pid globale o mantenere il pid nel coreStruct)
    if (pid != -1) {
        kill(pid, SIGKILL);
        pid = -1;  // Reset del pid
    }
}

void    handle_sigtstp(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nRicevuto SIGTSTP (Ctrl+Z). Questo comando è disabilitato.\n", 56);
	write(STDOUT_FILENO, "Minishell> ", 11);
}