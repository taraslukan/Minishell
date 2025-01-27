/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:01:41 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/27 18:04:38 by fluzi            ###   ########.fr       */
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

    if (!cmd || !cmd->args || !cmd->args[0] || !path_env)
        return NULL;

    split_path = ft_split(path_env, ':');
    if (!split_path)
        return NULL;

    while (split_path[i])
    {
        joined_path = ft_strjoin(split_path[i], "/");
        if (!joined_path)
            break;

        candidate_path = ft_strjoin(joined_path, cmd->args[0]);
        free(joined_path);
        if (!candidate_path)
            break;

        if (access(candidate_path, X_OK) == 0)
            break;

        free(candidate_path);
        candidate_path = NULL;
        i++;
    }
    free_matrix(split_path);
    return candidate_path;
}

void set_directory(t_comand *cmd, int *fd)
{
    int in_fd = -1;
    int out_fd = -1;

    if (cmd->in_file)
    {
        if (strcmp(cmd->in_file, PIPE_STD_IN) == 0 && fd && fd[0] >= 0)
            in_fd = fd[0];
        else
        {
            in_fd = open(cmd->in_file, O_RDONLY);
            if (in_fd == -1)
            {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
        }
        printf("cmd = %s %i -- %i\n",cmd->exe , fd[0], fd[1]);
        if (dup2(in_fd, STDIN_FILENO) == -1)
        {
            printf("%d %d\n", in_fd, STDIN_FILENO);
            perror("Error duplicating stdin");
            if (in_fd >= 0)
                close(in_fd);
            exit(EXIT_FAILURE);
        }
        if (in_fd >= 0)
            close(out_fd);
    }

    if (cmd->out_file)
    {
        if (strcmp(cmd->out_file, PIPE_STD_OUT) == 0 && fd && fd[1] >= 0)
            out_fd = fd[1];
        else
        {
            if (cmd->append)
                out_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                out_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (out_fd == -1)
            {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }
        }
        printf("cmd = %s %i -- %i\n",cmd->exe , fd[0], fd[1]);
        if (dup2(out_fd, STDOUT_FILENO) == -1)
        {
            perror("Error duplicating stdout");
            if (out_fd >= 0)
                close(out_fd);
            exit(EXIT_FAILURE);
        }
        if (out_fd >= 0)
            close(in_fd);
    }
}

void exe_func(t_comand *cmd, int *fd)
{
    char *path = find_path(cmd);

    if (!path)
    {
        fprintf(stderr, "Command not found: %s\n", cmd->exe);
        exit(EXIT_FAILURE);
    }

    set_directory(cmd, fd);

    if (execve(path, cmd->args, environ) == -1)
    {
        perror("execve");
        free(path);
        exit(EXIT_FAILURE);
    }

    free(path); // Non necessario, ma buone pratiche
}

