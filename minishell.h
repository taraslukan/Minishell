/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:22:41 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/19 18:22:43 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PIPE_STD_IN  "PIPE_STD_IN"
# define PIPE_STD_OUT  "PIPE_STD_OUT"
# define BLUE    "\001\033[1;34m\002"
# define GREEN   "\001\033[1;32m\002"
# define YELLOW  "\001\033[1;33m\002"
# define RESET   "\001\033[0m\002"
# include <stdio.h>    
# include <unistd.h>   
# include <limits.h>
# include <linux/limits.h>
# include <string.h>
# include <stdlib.h>   
# include <stdbool.h> 
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h> 
# include "new_read/read.h"
# include "structMinishell.h"
# include "libft/libft.h"
# include "utils/utils.h"
# include "signal/signal.h"    
# include "env/env.h"
# include "exv/exv.h"
# include "token/token.h"
# include "builtIn/builtIn.h"

#endif
