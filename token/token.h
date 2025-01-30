/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:08:42 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/30 12:51:11 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

// Standard libraries

// Project-specific headers
#include "../minishell.h"
#include "../structMinishell.h"

void        tokenize(t_coreStruct *core);
char		**token_master(char const *str, char c);
int			test(char *input);

size_t		count_pipe(char **matrix);
char		**pipe_splitter(char *str);

void 		print_functions(t_coreStruct *core);
void        print_command(const t_comand *cmd);

#endif /* MINISHELL_H */