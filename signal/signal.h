/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:30:21 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/20 15:38:51 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../minishell.h"
# include "../structMinishell.h"

void	handle_sigint(int signal);
void	init_signals(void);
void	handle_ctrl_d(char *line);

#endif