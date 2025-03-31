/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std_utils_exe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:22:11 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 13:38:47 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

int	validate_core_structure(t_core_struct *core)
{
	if (!core || core->pipe.number <= 0 || !core->functions)
	{
		write(2, "Invalid core structure\n", 23);
		return (0);
	}
	return (1);
}

void	handle_external_command(t_exec_manager *tools, pid_t *pids,
size_t index)
{
	manage_pipe(tools);
	pids[index] = fork();
	if (pids[index] == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pids[index] == 0)
	{
		if (tools->fd[0] > -1)
			close(tools->fd[0]);
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exe_func(tools);
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	wait_for_children(pid_t *pids, size_t num_children)
{
	int		status;
	size_t	j;

	j = 0;
	while (j < num_children)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_exit_status = 128 + WTERMSIG(status);
		j++;
	}
}

void	std_exv(t_core_struct *core)
{
	t_exec_manager	tools;
	pid_t			*pids;
	size_t			i;

	i = 0;
	pids = (pid_t *) malloc(sizeof(pid_t) * core->pipe.number);
	if (!validate_core_structure(core))
		exit(EXIT_FAILURE);
	manager_tools(&tools);
	while (i < core->pipe.number)
	{
		tools.cmd = &core->functions[i];
		tools.index = i;
		if (is_builtin(tools.cmd->exe))
			built_in_decision_menager(&tools);
		else
			handle_external_command(&tools, pids, i);
		manage_pipe_close_utils(&tools);
		i++;
	}
	wait_for_children(pids, core->pipe.number);
	close_fd(&tools);
}
