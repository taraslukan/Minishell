/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:20 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/16 15:38:25 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void    handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nRicevuto SIGINT (Ctrl+C). Premi Ctrl+D per uscire o continua...\n", 66);
	write(STDOUT_FILENO, "Minishell> ", 11);
}

void    handle_sigtstp(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nRicevuto SIGTSTP (Ctrl+Z). Questo comando è disabilitato.\n", 56);
	write(STDOUT_FILENO, "Minishell> ", 11);
}