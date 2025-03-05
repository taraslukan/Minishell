/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:32:15 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/05 15:36:46 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

static char	*allocate_token(char *start, size_t length, int flag1, int flag2)
{
	// Implementazione della funzione allocate_token
	// ...
	return NULL;
}

static char	*skip_token(char const *str, char c, bool *in_quotes, char *quote_char)
{
	// Implementazione della funzione skip_token
	// ...
	return (char *)str;
}

static void	handle_redirection(char const **str, char **tokens, size_t *index)
{
	char *start = (char *)*str;
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

static void	handle_regular_token(char const **str, char c, char **tokens, size_t *index, bool *in_quotes, char *quote_char)
{
	char *start = (char *)*str;
	*str = skip_token(*str, c, in_quotes, quote_char);
	tokens[(*index)++] = allocate_token(start, *str - start, 0, 0);
}

static void	process_token(char const **str, char c, char **tokens, size_t *index, bool *in_quotes, char *quote_char)
{
	if (**str != c)
	{
		if (**str == '>' || **str == '<')
		{
			handle_redirection(str, tokens, index);
		}
		else
		{
			handle_regular_token(str, c, tokens, index, in_quotes, quote_char);
		}
	}
	else
	{
		(*str)++;
	}
}

void	process_tokens(char const *str, char c, char **tokens)
{
	bool	in_quotes = false;
	char	quote_char = '\0';
	size_t	index = 0;

	while (*str)
	{
		process_token(&str, c, tokens, &index, &in_quotes, &quote_char);
	}
	tokens[index] = NULL;
}