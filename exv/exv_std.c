/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/27 18:08:32 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

extern char **environ;

void call_exe_func(t_comand *cmd, int *fd)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        if (fd[0] >= 0) close(fd[0]);
        if (fd[1] >= 0) close(fd[1]);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) // Processo figlio
    {
        
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        exe_func(cmd, fd);
        exit(EXIT_FAILURE); // Non dovrebbe mai arrivare qui
    }
    else // Processo padre
    {
        if (fd[1] >= 0) close(fd[1]);

        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid failed");
           // if (fd[0] >= 0) close(fd[0]);
            exit(EXIT_FAILURE);
        }

        // if (WIFEXITED(status))
        // {
        //     int exit_code = WEXITSTATUS(status);
        // }

        //if (fd[0] >= 0) close(fd[0]);
    }
}

void std_exv(t_coreStruct *core)
{
    size_t i = 0;

    int fd[2] = {-1, -1};

    if (core && core->pipe.number > 0)
    {
        
        if (pipe(fd) < 0)
        {
            perror("Pipe creation failed");
            exit(EXIT_FAILURE);
        }
        printf("\n \n%d %d\n\n", fd[0], fd[1]);
    }

    if (!core || core->pipe.number <= 0 || !core->functions)
    {
        fprintf(stderr, "Invalid core structure\n");
        exit(EXIT_FAILURE);
    }

    while (i < core->pipe.number)
    {
        if (is_builtin(core->functions[i].exe))
            execute_builtin(&core->functions[i]);
        else
        {
            call_exe_func(&core->functions[i], fd);
            if (fd[1] < 0)
            {
                close(fd[0]);
                close(fd[1]);
            }
        }

        i++;
    }
}