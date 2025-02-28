/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:43:23 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/28 14:39:14 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status;

void	start_process(t_core_struct *core)
{
	std_read(&core->read);
	if (strcmp(core->read.line, "") == 0)
		return ;
	printf("STAMPA%s", core->read.line);
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

void	std_directory_save(t_core_struct *core)
{
	core->stdin_copy = dup(STDIN_FILENO);
	if (core->stdin_copy == -1)
	{
		perror("dup stdin");
		exit(EXIT_FAILURE);
	}
	core->stdout_copy = dup(STDOUT_FILENO);
	if (core->stdout_copy == -1)
	{
		perror("dup stdout");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	t_core_struct	core;

	core.env = copy_env();
	std_directory_save(&core);
	fork_builde(&core);
	return (0);
}
