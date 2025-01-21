/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:54:43 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/21 16:52:45 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

extern char **environ;

char *find_path(t_comand *cmd)
{
    char **split_path;
    char *candidate_path = NULL;
    char *joined_path = NULL;
    char *path_env = getenv("PATH");
    int i = 0;

    if (!path_env)
        return NULL;

    split_path = ft_split(path_env, ':');
    if (!split_path)
        return NULL;
    while (split_path[i])
    {
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
    if (cmd->in_fd != -1)
    {
        if (dup2(cmd->in_fd, STDIN_FILENO) == -1)
        {
            perror("Error duplicating stdin");
            exit(EXIT_FAILURE);
        }
        close(cmd->in_fd);
    }
    if (cmd->out_fd != -1)
    {
        if (dup2(cmd->out_fd, STDOUT_FILENO) == -1)
        {
            perror("Error duplicating stdout");
            exit(EXIT_FAILURE);
        }
        close(cmd->out_fd);
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
    // Keep stdin_copy and stdout_copy open in case of reuse.
}

void exe_func(t_comand *cmd)
{
    char *path = find_path(cmd);

    if (!path)
    {
        fprintf(stderr, "Command not found: %s\n", cmd->exe);
        exit(EXIT_FAILURE);
    }
    set_directory(cmd);
    if (execve(path, cmd->args, environ) == -1)
    {
        perror("execve");
        free(path);
        exit(EXIT_FAILURE);
    }
    free(path);
    //reset_directory(cmd);
}

void one_fun_std_exe(t_comand *cmd)
{
    exe_func(cmd);
}

