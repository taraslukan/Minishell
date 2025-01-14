/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeManagement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:06:29 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/13 17:23:28 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

size_t count_pipe(char **matrix)
{
	size_t i;
	
	i = 0;
	while (matrix[i])
		i++;
	return(i);
}
char **pipe_splitter(char *str)
{
	char **matrix;

	matrix = ft_split(str, 124);
	return (matrix);
}