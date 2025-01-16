/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:45 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/16 14:09:04 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXV_H
#define EXV_H

// Standard libraries

// Project-specific headers
#include "../minishell.h"
#include "../structMinishell.h"

void	case_finder(t_coreStruct *core);
void	std_exv(t_comand *comand);

// exv_builtin_finder
bool    is_builtin(const char *cmd);
void    execute_builtin(const t_comand *cmd);
//void    execute_builtin(const t_comand *cmd);

#endif /* EXC_H */