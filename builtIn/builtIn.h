/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:54:08 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/03 14:47:25 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"
# include "../structMinishell.h"

void	print_env(char **env);
void	builtin_export(char ***env, const char *key);
void	builtin_unset(char ***env, const char *key);
void	ft_exit(t_core_struct *core);
void	ft_pwd(void);
void	ft_cd(int argc, char **argv);
void	ft_echo(int argc, char **argv);

#endif