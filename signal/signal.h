/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:30:21 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/16 15:32:14 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
#define SIGNAL_H

// Standard libraries

// Project-specific headers
#include "../minishell.h"
#include "../structMinishell.h"

void    handle_sigint(int sig);
void    handle_sigtstp(int sig);

#endif /* SIGNAL_H */