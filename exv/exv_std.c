/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:02:30 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/29 17:17:46 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

t_exec_manager call_exe_func(t_comand *cmd, int *old_fd, size_t i)
{
    int         fd[2]; 
    int         status;
    int         pipe_std_in;
    int         pipe_std_out;
    pid_t       pid;
    t_exec_manager  ret;

    fd[0] = -1;
    fd[1] = -1;

    if (i != cmd->core->pipe.number - 1)
    {
        if (pipe(fd))
        {
            perror("Pipe creation failed");
            exit(EXIT_FAILURE);
        }
    }
    ret.in = fd[0];
    ret.out = fd[1];
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

        
        if (i == 0)
        {
            pipe_std_in = -1;
            pipe_std_out = fd[1];
        }
        else if (i == cmd->core->pipe.number - 1)
        {
            pipe_std_in = old_fd[0]; 
            pipe_std_out = -1;        
        }
        else
        {
            pipe_std_in = old_fd[0];  
            pipe_std_out = fd[1];     
        }
        exe_func(cmd, pipe_std_in, pipe_std_out); 
        exit(EXIT_FAILURE);                     
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }

       
        if (i == 0)
        {
            printf("chiudo a:%d \n",fd[1] );
            close(fd[1]);
        }
        else if (i == cmd->core->pipe.number - 1)
        {
            printf("chiudo b:%d \n",old_fd[0]);
            close(old_fd[0]);
        }
        else
        {
             printf("chiudo c:%d \n",old_fd[0] );
              printf("chiudo d:%d \n",fd[1] );
            close(old_fd[0]); 
            close(fd[1]);
        }
    }
    return ret;
}

void std_exv(t_coreStruct *core)
{
    int old_fd[2];
    t_exec_manager temporany;

    old_fd[0] = -1;
    old_fd[1] = -1;
    if (!core || core->pipe.number <= 0 || !core->functions)
    {
        fprintf(stderr, "Invalid core structure\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < core->pipe.number; i++)
    {
        if (is_builtin(core->functions[i].exe))
        {
            execute_builtin(&core->functions[i]);
        }
        else
        {
            temporany = call_exe_func(&core->functions[i], old_fd, i);
            old_fd[0] = temporany.in;
            old_fd[1] = temporany.out;
        }
    }
    close(old_fd[0]);
    close(old_fd[1]);
}
