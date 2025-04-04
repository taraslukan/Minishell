/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:43:23 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 11:55:25 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status;

static bool	is_only_whitespace(const char *str)
{
	while (*str)
	{
		if (!(*str == ' ' || *str == '\t'))
			return (false);
		str++;
	}
	return (true);
}

static void	process_input(t_core_struct *core)
{
	std_read(core->env, &core->read);
	if (strcmp(core->read.line, "") == 0 || is_only_whitespace(core->read.line))
		return ;
	tokenize(core);
	std_exv(core);
	if (core->read.heredoc)
		unlink(core->read.in_file);
}

static void	main_loop(t_core_struct *core)
{
	init_signals();
	while (true)
		process_input(core);
}

int	main(void)
{
	t_core_struct	core;

	signal(SIGINT, handle_sigint);
	core.env = copy_env();
	main_loop(&core);
	safe_exit(&core, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
