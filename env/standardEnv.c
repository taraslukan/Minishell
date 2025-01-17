/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standardEnv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:39:04 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/17 12:32:49 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**copy_env(void)
{
	extern char **environ;
	char        **new_env;
	size_t      line;
	size_t      i;

	line = 0;
	i = 0;
	while (environ[line])
		line++;
	new_env = malloc((line +1) * sizeof(char *));
	if(!new_env)
		return(perror("malloc env"), NULL);
	while (i < line)
	{
	   new_env[i] = ft_strdup(environ[i]);
	   i++;
	}
	new_env[line] = NULL;
	return (new_env);
}

char	*get_env_value(char **env, const char *key)
{
	size_t  key_len;
	size_t  i;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=') 
			return &env[i][key_len + 1];
	}
	return (NULL);
}
static int	new_env_value(char ***env, const char *key, const char *value, size_t len)
{
	char	*new_env;
	char	*to_free;
	
	new_env = ft_rlc(*env, len, ((len + 2) * sizeof(char *)));
	if(!new_env)
		return(perror("malloc set val"), -1);
	*env = &new_env;
	(*env)[len] = malloc(strlen(key) + strlen(value) + 2);
	if(!(*env)[len])
		return(perror("malloc set val"), -1);
	to_free = ft_strjoin(key, "=");
	*(env)[len] = ft_strjoin(to_free, value);
	(*env)[len + 1] = NULL;
	free(to_free);
	return (0);
}
int	set_env_value(char ***env, const char *key, const char *value)
{
	size_t  key_len;
	size_t  i;
	char	*to_free;

	key_len = ft_strlen(key);
	i = 0;
	while((*env)[i])
	{
		if(ft_strncmp((*env)[i],key, key_len) == 0 && (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			*(env)[i] = malloc((key_len + ft_strlen(value)) * sizeof(char));
			if(!*(env)[i])
				return(perror("malloc set val"), -1);
			to_free = ft_strjoin(key, "=");
			*(env)[i] = ft_strjoin(to_free, value);
			free(to_free);
			return (0);
		}
	}
	return (new_env_value(env, key, value, i));
}

int unset_env_value(char ***env, const char *key)
{
    size_t key_len;
    size_t i;
    size_t j;

    key_len = ft_strlen(key);
    i = 0;
    while ((*env)[i])
	{
        if (ft_strncmp((*env)[i], key, key_len) == 0 && (*env)[i][key_len] == '=')
		{
            free((*env)[i]);
            j = i;
            while ((*env)[j + 1])
			{
                (*env)[j] = (*env)[j + 1];
                j++;
            }
            (*env)[j] = NULL;
            return 0;
        }
        i++;
    }
    return -1;
}



