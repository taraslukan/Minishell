/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:45 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/30 15:39:21 by fluzi            ###   ########.fr       */
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
void 	call_exe_func(t_exec_manager *tools);
void    manager_tools(t_exec_manager *tools);

void	exe_func(t_exec_manager *tools);
char 	*find_path(t_exec_manager *tools);
void	redirect_input(t_exec_manager *tools);
void 	redirect_output(t_exec_manager *tools);

void 	built_in_decision_menager(t_exec_manager *tools);
void 	exe_func_built_in_std(t_exec_manager *tools);
void	call_exe_func_built_in_std(t_exec_manager *tools);

void	manage_pipe_close_utils(t_exec_manager *tools);
void	manage_pipe_redirect_utils(t_exec_manager *tools);
void	manage_pipe(t_exec_manager *tools);

#endif /* EXC_H */