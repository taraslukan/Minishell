/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_finder_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:25:15 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/03 15:33:21 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

char	*find_heredoc_start(char *line)
{
	return strstr(line, "<<");
}

char	*skip_spaces(char *start)
{
	while (*start && *start == 32)
		start++;
	return (start);
}

char	*find_heredoc_delimiter(char *start)
{
	char	*end;
	
	end = start;
	while (*end && !isspace(*end))
		end++;
	return (end);
}

char	*extract_delimiter(char *start, char *end)
{
	if (!start || !end || end <= start)
		return NULL;
	return strndup(start, end - start);
}

char	*remove_heredoc(const char *input)
{
	char	*result;
	char	*heredoc_pos;
	char	*after_heredoc;
	
	result = strdup(input);
	if (!result)
		return NULL;
	heredoc_pos = strstr(result, "<<");
	if (heredoc_pos)
	{
		after_heredoc = heredoc_pos + 2;
		while (*after_heredoc == ' ')
			after_heredoc++;
		while (*after_heredoc && *after_heredoc != ' ')
			after_heredoc++;
		ft_memmove(heredoc_pos, after_heredoc, strlen(after_heredoc) + 1);
	}
	return (result);
}

