/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:39:02 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 13:39:07 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

char	*find_executable_path(t_exec_manager *tools, char **split_path)
{
	char	*candidate_path;
	char	*joined_path;
	int		i;

	i = 0;
	while (split_path[i])
	{
		joined_path = ft_strjoin(split_path[i], "/");
		if (!joined_path)
			break ;
		candidate_path = ft_strjoin(joined_path, tools->cmd->args[0]);
		free(joined_path);
		if (!candidate_path)
			break ;
		if (access(candidate_path, X_OK) == 0)
			return (candidate_path);
		free(candidate_path);
		candidate_path = NULL;
		i++;
	}
	return (NULL);
}

char	*find_path(t_exec_manager *tools)
{
	char	**split_path;
	char	*candidate_path;
	char	*path_env;

	candidate_path = NULL;
	path_env = getenv("PATH");
	if (!tools->cmd || !tools->cmd->args || !tools->cmd->args[0] || !path_env)
		return (NULL);
	split_path = ft_split(path_env, ':');
	if (!split_path)
		return (NULL);
	candidate_path = find_executable_path(tools, split_path);
	free_matrix(split_path);
	return (candidate_path);
}

void	redirect_input(t_exec_manager *tools)
{
	int	in_fd;

	in_fd = -1;
	if (tools->cmd->in_file)
	{
		if (strcmp(tools->cmd->in_file, PIPE_STD_IN) == 0
			&& tools->pipe_std_in >= 0)
			in_fd = tools->pipe_std_in;
		else
		{
			in_fd = open(tools->cmd->in_file, O_RDONLY);
			if (in_fd == -1)
				error_dup_input();
		}
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("Error duplicating stdin");
			if (in_fd >= 0)
				close(in_fd);
			exit(EXIT_FAILURE);
		}
		if (in_fd >= 0)
			close(in_fd);
	}
}

void	redirect_output(t_exec_manager *tools)
{
	int	out_fd;

	out_fd = -1;
	if (tools->cmd->out_file)
	{
		if (strcmp(tools->cmd->out_file, PIPE_STD_OUT) == 0
			&& tools->pipe_std_out >= 0)
			out_fd = tools->pipe_std_out;
		else
		{
			if (tools->cmd->append)
				out_fd = open(tools->cmd->out_file, O_WRONLY | O_CREAT
						| O_APPEND, 0644);
			else
				out_fd = open(tools->cmd->out_file, O_WRONLY
						| O_CREAT | O_TRUNC, 0644);
			if (out_fd == -1)
				error_dup_output();
		}
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			dup_close(out_fd);
		if (out_fd >= 0)
			close(out_fd);
	}
}

void	exe_func(t_exec_manager *tools)
{
	char	*path;
	int		stat;

	if (access(tools->cmd->exe, X_OK) == 0)
		path = tools->cmd->exe;
	else
		path = find_path(tools);
	if (!path)
	{
		fprintf(stderr, "Command not found: %s\n", tools->cmd->exe);
		exit(EXIT_FAILURE);
	}
	redirect_input(tools);
	redirect_output(tools);
	stat = execve(path, tools->cmd->args, tools->cmd->core->env);
	fprintf(stderr, "%d \n", stat);
	if (stat == -1)
	{
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	free(path);
}
