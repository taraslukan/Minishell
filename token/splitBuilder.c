/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitBuilder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:56:01 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/14 12:20:27 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// Funzione per avanzare il puntatore fino al termine del token
// Uso const perchè questo dato non viene modificato più fuori da questa funzione

static const char	*skip_token(const char *str, char c, bool *in_quotes, char *quote_char)
{
	while (*str && (*str != c || *in_quotes))
	{
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

// Funzione per contare le parole nella stringa
static size_t	count_words(const char *str, char c)
{
	size_t	count;
	bool	in_quotes;
	char	quote_char;

	count = 0;
	in_quotes = false;
	quote_char = '\0';
	while (*str)
	{
		if (*str != c)
		{
			count++;
			str = skip_token(str, c, &in_quotes, &quote_char);
		}
		else
			str++;
	}
	return (count);
}

// Funzione per allocare un token
static char	*allocate_token(const char *start, size_t length)
{
	char	*token;
	size_t	j;
	size_t	i;
	bool	in_quotes;
	char	quote_char;

	j = 0;
	i = 0;
	in_quotes = false;
	quote_char = '\0';
	token = malloc(sizeof(char) * (length + 1));
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

// Funzione per creare i token
static void	process_tokens(char const *str, char c, char **tokens)
{
	bool	in_quotes = false;
	char	quote_char = '\0';
	size_t	index = 0;

	while (*str)
	{
		if (*str != c)
		{
			const char	*start = str;
			str = skip_token(str, c, &in_quotes, &quote_char);
			tokens[index++] = allocate_token(start, str - start);
		}
		else
			str++;
	}
	tokens[index] = NULL;
}

// Funzione principale per dividere la stringa
char	**token_master(char const *str, char c)
{
	size_t	words_count;
	char	**tokens;

	if (!str)
		return (NULL);
	words_count = count_words(str, c);
	tokens = malloc(sizeof(char *) * (words_count + 1));
	if (!tokens)
		return (NULL);
	process_tokens(str, c, tokens);
	return (tokens);
}
