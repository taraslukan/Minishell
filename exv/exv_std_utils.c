/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_std_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:22:52 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/29 18:24:47 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

void    manager_tools(t_exec_manager *tools)
{
	tools->pipe_std_in = -1;
	tools->pipe_std_out = -1;
    tools->old_fd[0] = -1;
	tools->old_fd[1] = -1;
    tools->fd[0] = -1;
	tools->fd[1] = -1;
}