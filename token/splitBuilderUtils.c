/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitBuilderUtils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:44:38 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 13:47:41 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	handle_special_tokens(char const **str, char **tokens,
	size_t *index)
{
	const char	*start;

	start = *str;
	if (**str == '>' && *(*str + 1) == '>')
	{
		tokens[(*index)++] = allocate_token(start, 2, 0, 0);
		*str += 2;
	}
	else if (**str == '>' || **str == '<')
	{
		tokens[(*index)++] = allocate_token(start, 1, 0, 0);
		(*str)++;
	}
}

void	process_tokens(char const *str, char c, char **tokens)
{
	bool	in_quotes;
	char	quote_char;
	size_t	index;
	char	*start;

	in_quotes = false;
	quote_char = '\0';
	index = 0;
	while (*str)
	{
		if (*str != c)
		{
			start = (char *)str;
			if (*str == '>' || *str == '<')
			{
				handle_special_tokens(&str, tokens, &index);
				continue ;
			}
			str = skip_token(str, c, &in_quotes, &quote_char);
			tokens[index++] = allocate_token(start, str - start, 0, 0);
		}
		else
			str++;
	}
	tokens[index] = NULL;
}
