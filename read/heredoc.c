/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:08:28 by lukan             #+#    #+#             */
/*   Updated: 2025/02/03 15:35:59 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

char	*ft_substr_tarl(const char *s, unsigned int start, size_t len)
{
    char	*ret;
    size_t	s_len;
    size_t	sub_len;

    if (!s)
        return (NULL);

    s_len = ft_strlen(s);

    if (start >= s_len)
        return (ft_strdup(""));

    sub_len = s_len - start;
    if (sub_len > len)
        sub_len = len;
    ret = (char *)malloc(sizeof(char) * (sub_len + 1));
    if (!ret)
        return (NULL);
    ft_strlcpy(ret, s + start, sub_len + 1);

    return (ret);
}

// Funzione per controllare il delimitatore
bool check_delimiter(const char *str, const char *delimiter)
{
    int len;
    int end;

    if (!str || !delimiter)
        return (false);

    len = ft_strlen(str);
    end = len - 1;

    if (end >= 0 && str[end] == '\n')
        end--;

    if (end >= 0 && str[end] == ' ')
        return (false);

    int start = end;
    while (start >= 0 && str[start] != ' ')
	{
        start--;
	}
	return (ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0);
}


char	*save_delimiter(int i, char *input)
{
	int		start;
	int		len;
	char	*delimiter;

	start = i;
	while (input[i] && input[i] > ' ')
		i++;
	len = i - start;
	delimiter = ft_substr_tarl(input, start, len);
	return (delimiter);
}

char	*here_loop(char *delimiter)
{
	char	*line;
	char	*fullstring;
	char	*temp;

	fullstring = ft_strdup("");
	while (1)
	{
		line = readline("heredoc:(.y.) --> ");
		if (!line)
			break;
		if (check_delimiter(line, delimiter))
		{
			free(line);
			break;
		}
		temp = fullstring;
		fullstring = ft_strjoin(fullstring, line);
		fullstring = ft_strjoin(fullstring, "\n");
		free(temp);
		free(line);
	}
	return (fullstring);
}


char	*tl_check_heredoc(char *input)
{
	int		i;
	char	*heredoc_pw;
	char	*heredocinput;
	
	if (!input)
		return (NULL);
	i = 0;
	heredoc_pw = NULL;
	heredocinput = NULL;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] && input[i] <= ' ')
				i++;
			heredoc_pw = save_delimiter(i, input);
			heredocinput = here_loop(heredoc_pw);
			break;
		}
		i++;
	}
	return (heredocinput);
}
