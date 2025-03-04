/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/04 17:21:47 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

void	manage_pipe_close_utils(t_exec_manager *tools)
{
	if (tools->index == 0 && tools->fd[1] > -1)
		close(tools->fd[1]);
	else if (tools->index == tools->cmd->core->pipe.number - 1
		&& tools->old_fd[0] > -1)
		close(tools->old_fd[0]);
	else
	{
		if (tools->old_fd[0] > -1)
			close(tools->old_fd[0]);
		if (tools->fd[1] > -1)
			close(tools->fd[1]);
	}
}

void	manage_pipe_redirect_utils(t_exec_manager *tools)
{
	if (tools->index == 0)
	{
		tools->pipe_std_in = -1;
		tools->pipe_std_out = tools->fd[1];
	}
	else if (tools->index == tools->cmd->core->pipe.number - 1)
	{
		tools->pipe_std_in = tools->old_fd[0];
		tools->pipe_std_out = -1;
	}
	else
	{
		tools->pipe_std_in = tools->old_fd[0];
		tools->pipe_std_out = tools->fd[1];
	}
}

void	manage_pipe(t_exec_manager *tools)
{
	if (tools->fd[0] != -1)
	{
		tools->old_fd[0] = tools->fd[0];
		tools->old_fd[1] = tools->fd[1];
	}
	if (tools->index != (tools->cmd->core->pipe.number - 1))
	{
		if (pipe(tools->fd))
		{
			perror("Pipe creation failed");
			safe_exit(tools->cmd->core, EXIT_FAILURE);
		}
	}
	else
	{
		tools->fd[0] = -1;
		tools->fd[1] = -1;
	}
	manage_pipe_redirect_utils(tools);
}

void	close_fd(t_exec_manager *tools)
{
	if (tools->old_fd[0] > -1)
		close(tools->old_fd[0]);
	if (tools->old_fd[1] > -1)
		close(tools->old_fd[1]);
	if (tools->fd[0] > -1)
		close(tools->fd[0]);
	if (tools->fd[1] > -1)
		close(tools->fd[1]);
}
