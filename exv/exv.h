/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:45 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/27 17:17:06 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXV_H
#define EXV_H

// Standard libraries

// Project-specific headers
#include "../minishell.h"
#include "../structMinishell.h"

void    execute_builtin(const t_comand *cmd);
bool    is_builtin(const char *cmd);

void    call_exe_func(t_comand *cmd, int *fd);
void    std_exv(t_coreStruct *core);

char    *find_path(t_comand *cmd);
void    set_directory(t_comand *cmd, int *fd);
void    exe_func(t_comand *cmd, int *fd);

#endif /* EXC_H */