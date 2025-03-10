/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitBuilder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:56:01 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/10 16:02:23 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static const char	*skip_token(const char *str, char c, bool *in_quotes,
char *quote_char)
{
	while (*str && (*str != c || *in_quotes))
	{
		if ((*str == '>' || *str == '<') && !*in_quotes)
			break ;
		if (*str == '>' && *(str + 1) == '>' && !*in_quotes)
			break ;
		if ((*str == 39 || *str == 34) && !*in_quotes)
		{
			*in_quotes = true;
			*quote_char = *str;
		}
		else if (*str == *quote_char && *in_quotes)
			*in_quotes = false;
		str++;
	}
	return (str);
}

static size_t	count_words(const char *str, char c, size_t	count,
bool	in_quotes)
{
	char	quote_char;

	quote_char = '\0';
	while (*str)
	{
		if (*str != c)
		{
			count++;
			if (*str == '>' && *(str + 1) == '>')
			{
				count++;
				str += 2;
			}
			else if (*str == '>' || *str == '<')
			{
				count++;
				str++;
			}
			else
				str = skip_token(str, c, &in_quotes, &quote_char);
		}
		else
			str++;
	}
	return (count);
}

static char	*allocate_token(const char *start, size_t length, size_t j,
size_t i)
{
	char	*token;
	bool	in_quotes;
	char	quote_char;

	in_quotes = false;
	quote_char = '\0';
	token = malloc(sizeof(char) * (length + 1));
	if (!token)
		return (NULL);
	while (i < length)
	{
		if ((start[i] == '\'' || start[i] == '\"') && !in_quotes)
		{
			in_quotes = true;
			quote_char = start[i];
		}
		else if (start[i] == quote_char && in_quotes)
			in_quotes = false;
		else
			token[j++] = start[i];
		i++;
	}
	return (token[j] = '\0', token);
}

static void	process_tokens(char const *str, char c, char **tokens)
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
			start = (char *) str;
			if (*str == '>' && *(str + 1) == '>')
			{
				tokens[index++] = allocate_token(start, 2, 0, 0);
				str += 2;
			}
			else if (*str == '>' || *str == '<')
			{
				tokens[index++] = allocate_token(start, 1, 0, 0);
				str++;
			}
			else
			{
				str = skip_token(str, c, &in_quotes, &quote_char);
				tokens[index++] = allocate_token(start, str - start, 0, 0);
			}
		}
		else
			str++;
	}
	tokens[index] = NULL;
}

char	**token_master(char const *str, char c)
{
	size_t	words_count;
	char	**tokens;

	if (!str)
		return (NULL);
	words_count = count_words(str, c, 0, false);
	tokens = malloc(sizeof(char *) * (words_count + 1));
	if (!tokens)
		return (NULL);
	process_tokens(str, c, tokens);
	return (tokens);
}
