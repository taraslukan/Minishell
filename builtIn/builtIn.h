/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:54:08 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/20 15:37:05 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
#define BUILT_IN_H

#include "../minishell.h"
#include "../structMinishell.h"

void    print_env(char **env);
void    builtin_export(char ***env, const char *key, const char *value);
void    builtin_unset(char ***env, const char *key);
void    ft_exit();
void    ft_pwd();

void	ft_echo(int argc, char **argv);


#endif /* BUILT_IN_FUNCTION_H */