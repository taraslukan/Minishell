/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:30:21 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/03 15:36:22 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
#define SIGNAL_H

#include "../minishell.h"
#include "../structMinishell.h"

void	handle_sigint(int sig);
void	handle_sigtstp(int sig);

#endif