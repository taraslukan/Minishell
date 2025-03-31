/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:08:42 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 13:51:30 by fluzi            ###   ########.fr       */
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
void		process_tokens(char const *str, char c, char **tokens);
t_comand	comand_write(char **matrix, bool pipe_in, bool pipe_out,
				t_core_struct *core);
char		*allocate_token(const char *start, size_t length, size_t j,
				size_t i);
const char	*skip_token(const char *str, char c, bool *in_quotes,
				char *quote_char);

#endif