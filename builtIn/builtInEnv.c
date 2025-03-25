/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtInEnv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:51:55 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/25 17:32:47 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

static bool	is_only_tabs_or_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (true);
		str++;
	}
	return (false);
}

void	print_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

void	print_env_export(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

void	builtin_export(char ***env, const char *key)
{
	char	**split;
	
	if(ft_strlen(key) < 2 && is_only_tabs_or_spaces(key))
		print_env_export((char **) env);
	else 
	{
		split = ft_split(key, '=');
		if(matrix_len(split) < 2)
		{
			free(split);
			return;
		}
		if (set_env_value(env, split[0], split[1]) == -1)
			perror("export: failed to set \n");
		free(split);
	}
}

void	builtin_unset(char ***env, const char *key)
{
	char	**split;

	if(!is_only_tabs_or_spaces(key))
		return;
	split = ft_split(key, '=');
	if (unset_env_value(env, split[0]) == -1)
		perror("unset:  not found\n");
	free(split);
}
