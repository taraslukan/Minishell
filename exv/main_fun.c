/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:54:43 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/20 15:14:56 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

extern char **environ;  

char    *find_path(t_comand *cmd)
{
    char    **split_path;
    char    *candidate_path;
    char    *joined_path;
    int     i;

    i = 0;
    split_path = ft_split(getenv("PATH"), ':');
    candidate_path = NULL;
    joined_path = NULL;
    while (split_path[i]) {
        joined_path = ft_strjoin(split_path[i], "/");
        candidate_path = ft_strjoin(joined_path, cmd->exe);
        free(joined_path);
        if (access(candidate_path, X_OK) == 0)
            break;
        free(candidate_path);
        candidate_path = NULL;
        i++;
    }
    free_matrix(split_path);
    return candidate_path;
}

void set_directory(t_comand *cmd)
{
    if (cmd->in_file) {
        int fd_in = open(cmd->in_file, O_RDONLY);
        if (fd_in == -1 || access(cmd->in_file, R_OK) != 0)
        {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd_in, STDIN_FILENO) == -1)
        {
            perror("Error duplicating stdin");
            exit(EXIT_FAILURE);
        }
        close(fd_in);
    }
    if (cmd->out_file)
    {
        int fd_out;
        if (cmd->append)
            fd_out = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd_out = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd_out == -1)
        {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd_out, STDOUT_FILENO) == -1)
        {
            perror("Error duplicating stdout");
            exit(EXIT_FAILURE);
        }
        close(fd_out);
    }
}


void reset_directory(t_comand *cmd)
{
    if (dup2(cmd->core->stdin_copy, STDIN_FILENO) == -1)
    {
        perror("dup2 stdin");
        exit(EXIT_FAILURE);
    }
    if (dup2(cmd->core->stdout_copy, STDOUT_FILENO) == -1)
    {
        perror("dup2 stdout");
        exit(EXIT_FAILURE);
    }
    close(cmd->core->stdin_copy);
    close(cmd->core->stdout_copy);
}
void	exe_func(t_comand *cmd)
{
	char	*path;

	path = find_path(cmd);
    set_directory(cmd);
	if (!path)
		exit(0);
	if (execve(path, cmd->args, environ) == -1)
	{
		perror("Error\n");
		free(path);
		free_matrix(cmd->args);
	}
    reset_directory(cmd);
	free(path);
	
}

void one_fun_std_exe(t_comand *cmd)
{
    exe_func(cmd);
    // char *path = find_path(cmd);
    // if (!path) 
    // {
    //     fprintf(stderr, "Command not found: %s\n", cmd->exe);
    //     exit(EXIT_FAILURE);
    // }
    // set_directory(cmd);
    // if (execve(path, cmd->args, environ) == -1)
    // {
    //     perror("execve");
    //     free(path);
    //     exit(EXIT_FAILURE);
    // }
    // free(path);
    // if (cmd->in_file && cmd->out_file)
    //      reset_directory(cmd);
}
