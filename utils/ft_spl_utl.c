/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spl_utl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:15:26 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/28 14:25:52 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	count_words(char const *str, char c)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static void	handle_special_symbols(char const **str, char **ptr_ret,
size_t *index)
{
	if (**str == '<' && *(*str + 1) == '<')
	{
		ptr_ret[(*index)++] = ft_strdup("<<");
		*str += 2;
	}
	else
	{
		ptr_ret[(*index)++] = ft_strndup(*str, 1);
		*str += 1;
	}
}

static void	handle_regular_word(char const **str, char c, char **ptr_ret,
size_t *index)
{
	size_t	end_wrd;

	end_wrd = 0;
	while (**str && **str != c && **str != '<' && **str != '>')
	{
		end_wrd++;
		(*str)++;
	}
	ptr_ret[(*index)++] = ft_substr(*str - end_wrd, 0, end_wrd);
}

char	**ft_spl_utl(char const *str, char c)
{
	char	**ptr_ret;
	size_t	index;

	if (!str)
		return (NULL);
	ptr_ret = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (ptr_ret == NULL)
		return (NULL);
	index = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else if (*str == '<' || *str == '>')
			handle_special_symbols(&str, ptr_ret, &index);
		else
			handle_regular_word(&str, c, ptr_ret, &index);
	}
	ptr_ret[index] = NULL;
	return (ptr_ret);
}
