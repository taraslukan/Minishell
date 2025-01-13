/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitBuilder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico2 <federico2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:16:56 by federico2         #+#    #+#             */
/*   Updated: 2025/01/13 14:07:09 by federico2        ###   ########.fr       */
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
			printf("%s", str);
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
	size_t	count = 0;
	bool	in_quotes = false;
	char	quote_char = '\0';

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
	char	*token = malloc(sizeof(char) * (length + 1));
	if (!token)
		return (NULL);
	for (size_t i = 0; i < length; i++)
		token[i] = start[i];
	token[length] = '\0';
	return (token);
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