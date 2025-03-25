/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standardEnv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:39:04 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/20 17:04:48 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

size_t	count_env_lines(void)
{
	extern char	**environ;
	size_t		count;

	count = 0;
	while (environ[count])
		count++;
	return (count);
}

char	**copy_env(void)
{
	extern char	**environ;
	char		**new_env;
	size_t		line_count;
	size_t		i;

	line_count = 0;
	while (environ[line_count])
		line_count++;
	new_env = malloc((line_count + 1) * sizeof(char *));
	if (!new_env)
		return (perror("malloc env"), NULL);
	i = 0;
	while (i < line_count)
	{
		new_env[i] = ft_strdup(environ[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			return (free(new_env), perror("malloc env"), NULL);
		}
		i++;
	}
	new_env[line_count] = NULL;
	return (new_env);
}

char	*get_env_value(char **env, const char *key)
{
	size_t	key_len;
	size_t	i;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (&env[i][key_len + 1]);
		i++;
	}
	return (NULL);
}

char	*create_env_entry(const char *key, const char *value)
{
	char	*entry;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, value);
	free(temp);
	return (entry);
}

int	new_env_value(char ***env, const char *key,
const char *value, size_t len)
{
	char	**new_env;
	char	*new_entry;

	new_env = realloc(*env, (len + 2) * sizeof(char *));
	if (!new_env)
		return (perror("realloc set val"), -1);
	*env = new_env;
	new_entry = create_env_entry(key, value);
	if (!new_entry)
		return (perror("malloc set val"), -1);
	(*env)[len] = new_entry;
	(*env)[len + 1] = NULL;
	return (0);
}
