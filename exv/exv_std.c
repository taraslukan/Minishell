/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/04 14:05:05 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

void	manage_pipe_close_utils(t_exec_manager *tools)
{
		if (tools->index == 0)
			close(tools->fd[1]);
		else if (tools->index == tools->cmd->core->pipe.number - 1)
			close(tools->old_fd[0]);
		else
		{
			close(tools->old_fd[0]); 
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
void manage_pipe(t_exec_manager *tools)
{
	if(tools->fd[0] != -1)
	{
		tools->old_fd[0] = tools->fd[0];
		tools->old_fd[1] = tools->fd[1];
	}
	if (tools->index != (tools->cmd->core->pipe.number - 1))
	{
		if (pipe(tools->fd))
		{
			perror("Pipe creation failed");
			exit(EXIT_FAILURE);
		}
	}
	manage_pipe_redirect_utils(tools);
}


void std_exv(t_coreStruct *core)
{
    t_exec_manager   tools;
    size_t           i;
    pid_t           pids[core->pipe.number];
    int             status;

    i = 0;
    if (!core || core->pipe.number <= 0 || !core->functions)
    {
        fprintf(stderr, "Invalid core structure\n");
        exit(EXIT_FAILURE);
    }
    manager_tools(&tools);
    while (i < core->pipe.number)
    {
        tools.cmd = &core->functions[i];
        tools.index = i;
        if (is_builtin(core->functions[i].exe))
            built_in_decision_menager(&tools);
        else
        {
            manage_pipe(&tools);
            pids[i] = fork();
            if (pids[i] == -1)
            {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }
            if (pids[i] == 0) // Processo figlio
            {
                signal(SIGINT, SIG_DFL);
                signal(SIGTSTP, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);
                exe_func(&tools);
                exit(EXIT_FAILURE);
            }
        }
        manage_pipe_close_utils(&tools);
        i++;
    }

    for (size_t j = 0; j < core->pipe.number; j++)
    {
        waitpid(pids[j], &status, 0);
        if (WIFEXITED(status))
            g_last_exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_last_exit_status = 128 + WTERMSIG(status);
    }

    close(tools.old_fd[0]);
    close(tools.old_fd[1]);
    close(tools.fd[0]);
    close(tools.fd[1]);
}
