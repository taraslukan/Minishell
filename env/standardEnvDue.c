/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standardEnvDue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:24:39 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/20 17:01:32 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	set_env_value(char ***env, const char *key, const char *value)
{
	size_t	key_len;
	size_t	i;
	char	*new_entry;

	key_len = ft_strlen(key);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, key_len) == 0
					&& (*env)[i][key_len] == '=')
		{
			new_entry = create_env_entry(key, value);
			if (!new_entry)
				return (perror("malloc set val"), -1);
			free((*env)[i]);
			(*env)[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (new_env_value(env, key, value, i));
}

void	shift_env_entries(char ***env, size_t start)
{
	size_t	i;

	i = start;
	while ((*env)[i + 1])
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	(*env)[i] = NULL;
}

int	unset_env_value(char ***env, const char *key)
{
	size_t	key_len;
	size_t	i;

	key_len = ft_strlen(key);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, key_len) == 0
			&& (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			while ((*env)[i + 1])
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;
			return (0);
		}
		i++;
	}
	return (-1);
}
