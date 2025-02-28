/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:39:24 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/19 18:27:45 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"
# include "../structMinishell.h"

size_t	count_env_lines(void);
char	**copy_env(void);
char	*get_env_value(char **env, const char *key);
char	*create_env_entry(const char *key, const char *value);
int		new_env_value(char ***env, const char *key, const char *value,
			size_t len);
int		set_env_value(char ***env, const char *key, const char *value);
void	shift_env_entries(char ***env, size_t start);
int		unset_env_value(char ***env, const char *key);

#endif /* EXC_H */