/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:45 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/29 18:25:01 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXV_H
#define EXV_H

#include "../minishell.h"
#include "../structMinishell.h"

typedef struct s_exec_manager
{
	t_comand	*cmd;
	size_t		index;
	int			pipe_std_in;
	int			pipe_std_out;
	int 		old_fd[2];
	int			fd[2];
	
}t_exec_manager;

void	execute_builtin(const t_comand *cmd);
bool	is_builtin(const char *cmd);
void	std_exv(t_coreStruct *core);
char	*find_path(t_comand *cmd);
void	set_directory(t_comand *cmd, int pipe_std_in, int pipe_std_out);
void	exe_func(t_comand *cmd, int pipe_std_in, int pipe_std_out);
void 	call_exe_func(t_exec_manager *tools);
void    manager_tools(t_exec_manager *tools);

#endif /* EXC_H */