/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_built_in_exv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:16:13 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/03 14:50:22 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

void	call_exe_func_built_in_std(t_exec_manager *tools)
{
	int		status;
	pid_t	pid;

	manage_pipe(tools);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exe_func_built_in_std(tools);
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (waitpid(pid, &status, 0) == -1)
		exit(EXIT_FAILURE);
	manage_pipe_close_utils(tools);
}

void	exe_func_built_in_std(t_exec_manager *tools)
{
	char	*cmd;

	cmd = tools->cmd->exe;
	if (strcmp(cmd, "echo") == 0)
	{
		redirect_input(tools);
		redirect_output(tools);
		ft_echo(tools->cmd->argc, tools->cmd->args);
	}
	else if (strcmp(cmd, "pwd") == 0)
	{
		redirect_input(tools);
		redirect_output(tools);
		ft_pwd();
	}
	else if (strcmp(cmd, "env") == 0)
	{
		redirect_input(tools);
		redirect_output(tools);
		print_env(tools->cmd->core->env);
	}
	free(cmd);
}

void	built_in_decision_menager(t_exec_manager *tools)
{
	char	*cmd;

	cmd = tools->cmd->exe;
	if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "pwd") == 0
		|| strcmp(cmd, "env") == 0)
		call_exe_func_built_in_std(tools);
	else if (strcmp(cmd, "cd") == 0)
		ft_cd(tools->cmd->argc, tools->cmd->args);
	else if (strcmp(cmd, "export") == 0)
		builtin_export(&tools->cmd->core->env, tools->cmd->args[1]);
	else if (strcmp(cmd, "unset") == 0)
		printf("unset");
	else if (strcmp(cmd, "exit") == 0)
		ft_exit(tools->cmd->core);
	free(cmd);
}
