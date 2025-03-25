/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtInecho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:35:03 by lukan             #+#    #+#             */
/*   Updated: 2025/03/25 15:32:45 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

bool	is_option_n(const char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

char	*remove_quotes(const char *str)
{
	char	*result;
	size_t	len;
	size_t	i;
	size_t	j;

	len = strlen(str);
	result = malloc(len + 1);
	i = 0;
	j = 0;
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	ft_echo(int argc, char **argv)
{
	char	*clean_arg;
	bool	newline;
	int		i;

	newline = true;
	i = 1;
	if (i < argc && is_option_n(argv[i]))
	{
		newline = false;
		i++;
	}
	while (i < argc)
	{
		clean_arg = remove_quotes(argv[i]);
		if (!clean_arg)
			return ;
		printf("%s", clean_arg);
		free(clean_arg);
		i++;
		if (i < argc)
			printf(" ");
	}
	if (newline)
		printf("\n");
	return ;
}
