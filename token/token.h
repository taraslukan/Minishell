/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:08:42 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/10 15:05:27 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../minishell.h"
# include "../structMinishell.h"

typedef struct s_token_utils
{
	int		index;
	bool	pipe_in;
	bool	pipe_out;
	int		arg_count;

}	t_token_utils;

char		**token_master(char const *str, char c);
int			test(char *input);
size_t		count_pipe(char **matrix);
char		**pipe_splitter(char *str);
void		print_functions(t_core_struct *core);
void		print_command(const t_comand *cmd);
void		tokenize(t_core_struct *core);
t_comand	comand_write(char **matrix, bool pipe_in, bool pipe_out,
				t_core_struct *core);

#endif