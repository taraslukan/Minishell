/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:54:47 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/03 14:55:08 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../minishell.h"
# include "../structMinishell.h"

void	*ft_rlc(void *list, size_t old_size, size_t new_size);
int		free_matrix(char **matrix);
char	*ft_itoa(int num);
char	*ft_strndup(const char *s, size_t n);

#endif