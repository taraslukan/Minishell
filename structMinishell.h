/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structMinishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:03:24 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/03 14:58:47 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTMINISHELL_H
# define STRUCTMINISHELL_H

# include <stdbool.h>
# include <stddef.h>

extern int						g_last_exit_status;
typedef struct s_core_struct	t_core_struct;

typedef struct s_read
{
	char	*std;
	char	*line;
	char	*in_file;
	char	*delimiter;
	bool	heredoc;
	bool	success;
	bool	global_var_enable;

}	t_read;

typedef struct s_comand
{
	char			*exe;
	int				argc;
	char			**args;
	char			*in_file;
	char			*out_file;
	bool			append;
	t_core_struct	*core;
}	t_comand;

typedef struct s_pipeAdmin
{
	bool	exists;
	size_t	number;
}	t_pipeAdmin;

typedef struct s_core_struct
{
	t_comand	*functions;
	t_pipeAdmin	pipe;
	t_read		read;
	char		**pipe_split;
	char		**env;
}	t_core_struct;

#endif /* STRUCTMINISHELL_H */
