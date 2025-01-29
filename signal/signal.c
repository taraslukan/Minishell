/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:20 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/29 19:44:56 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"  // Aggiungi questa riga

void handle_sigint(int sig)
{
    (void)sig;
    exit(0);
}

void    handle_sigtstp(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nRicevuto SIGTSTP (Ctrl+Z). Questo comando è disabilitato.\n", 56);
	write(STDOUT_FILENO, "Minishell> ", 11);
}