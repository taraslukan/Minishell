/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:08:42 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/14 15:54:29 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

// Standard libraries

// Project-specific headers
#include "../minishell.h"
#include "../structMinishell.h"


char		**token_master(char const *str, char c);
int			test(void);

size_t		count_pipe(char **matrix);
char		**pipe_splitter(char *str);

void 		print_functions(t_coreStruct *core);

#endif /* MINISHELL_H */