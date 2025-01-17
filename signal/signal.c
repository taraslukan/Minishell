/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:20 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/17 11:54:44 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"  // Aggiungi questa riga

void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nRicevuto SIGINT (Ctrl+C). Terminato il processo figlio.\n", 58);

    // // Uccidi il processo figlio (se necessario)
    // if (pid != -1) {
    //     kill(pid, SIGKILL);
    //     pid = -1;  // Reset del pid
    // }

    // Esci dal processo figlio
    exit(0);
}

void    handle_sigtstp(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nRicevuto SIGTSTP (Ctrl+Z). Questo comando è disabilitato.\n", 56);
	write(STDOUT_FILENO, "Minishell> ", 11);
}