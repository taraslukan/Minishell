/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtInEnv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:51:55 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/04 15:55:15 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

void	print_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	exit(0);
}

void	builtin_export(char ***env, const char *key)
{
	char	**split;

	split = ft_split(key, '=');
	if (set_env_value(env, split[0], split[1]) == -1)
		perror("export: failed to set \n");
	free(split);
}

void	builtin_unset(char ***env, const char *key)
{
	char	**split;

	split = ft_split(key, '=');
	if (unset_env_value(env, split[0]) == -1)
		perror("unset:  not found\n");
	free(split);
}
