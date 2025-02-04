/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:39:24 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/04 14:09:04 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H
#include "../minishell.h"
#include "../structMinishell.h"

char    **copy_env(void);
char    *get_env_value(char **env, const char *key);
int	    set_env_value(char ***env, const char *key, const char *value);
int     unset_env_value(char ***env, const char *key);

#endif /* EXC_H */