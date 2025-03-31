/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:20 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 13:52:13 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h" 

void	handle_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_ctrl_d(char *line)
{
	if (!line)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}
