/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtInEnv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:51:55 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/16 13:56:33 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

void print_env(char **env)
{
    size_t  i;

    i = 0;
    while (env[i])
        printf("%s\n", env[i++]);
}

void builtin_export(char ***env, const char *key, const char *value)
{
    if (set_env_value(env, key, value) == -1) {
        perror("export: failed to set \n");
    }
}

void builtin_unset(char ***env, const char *key)
{
    if (unset_env_value(env, key) == -1) {
        perror("unset:  not found\n");
    }
}
