/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:43:23 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/03 14:50:48 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status;

bool	is_only_tabs_or_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (false);
		str++;
	}
	return (true);
}

void	start_process(t_core_struct *core)
{
	std_read(&core->read);
	if (strcmp(core->read.line, "") == 0)
		return ;
	if (is_only_tabs_or_spaces(core->read.line))
		return ;
	tokenize(core);
	std_exv(core);
	if (core->read.heredoc)
		unlink(core->read.in_file);
}

static void	fork_builde(t_core_struct *core)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		start_process(core);
}

int	main(void)
{
	t_core_struct	core;

	core.env = copy_env();
	fork_builde(&core);
	safe_exit(&core, 0);
	return (0);
}
