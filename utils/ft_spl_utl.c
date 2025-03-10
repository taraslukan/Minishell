/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spl_utl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:15:26 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/10 16:01:42 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	handle_quotes(const char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	if (str[*i] == '\"')
		(*i)++;
	else
		return (0);
	return (1);
}

static int	pipe_count_words(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (!handle_quotes(str, &i))
				return (0);
		}
		else if (str[i] == '|')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static void	parse_segment(const char *s, int *i, int *j)
{
	*j = 0;
	while (s[*i])
	{
		if (s[*i] == '\"')
		{
			(*i)++;
			(*j)++;
			while (s[*i] && s[*i] != '\"')
			{
				(*i)++;
				(*j)++;
			}
		}
		if (s[*i] == '|')
		{
			(*i)++;
			(*j)++;
			break ;
		}
		(*i)++;
		(*j)++;
	}
}

static char	**pipe_split_words(const char *s, char **result, int pipe_count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (k < pipe_count)
	{
		parse_segment(s, &i, &j);
		if (s[i] == '\0')
		{
			i++;
			j++;
		}
		result[k] = strndup(s +(i - j), j - 1);
		k++;
	}
	result[k] = NULL;
	return (result);
}

char	**ft_pipe_split(char const *s, char c)
{
	char	**result;
	char	**tmp_matrix;
	int		word_count;
	int		l;

	(void)c;
	if (!s)
		return (0);
	word_count = pipe_count_words(s);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (0);
	tmp_matrix = pipe_split_words(s, result, word_count);
	l = 0;
	while (result[l])
		l++;
	return (tmp_matrix);
}
