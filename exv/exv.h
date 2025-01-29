/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:45 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/29 17:16:56 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXV_H
#define EXV_H

// Standard libraries

// Project-specific headers
#include "../minishell.h"
#include "../structMinishell.h"

typedef struct s_t_exec_manager
{
    int         old_in;
    int         old_out;

    int         pipe_std_in;
    int         pipe_std_out;
}t_exec_manager;

void        execute_builtin(const t_comand *cmd);
bool        is_builtin(const char *cmd);

t_exec_manager  call_exe_func(t_comand *cmd, int *old_fd, size_t i) ;
void        std_exv(t_coreStruct *core);

char        *find_path(t_comand *cmd);
void        set_directory(t_comand *cmd, int pipe_std_in, int pipe_std_out);
void        exe_func(t_comand *cmd, int pipe_std_in, int pipe_std_out);

#endif /* EXC_H */