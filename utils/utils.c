/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:32:07 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/31 15:19:15 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void *ft_rlc(void *list, size_t old_size, size_t new_size)
{
    size_t          copy_size;
    unsigned char   *new_list;

    if (list == NULL)
        return malloc(new_size);
    if (new_size == 0)
        return (free(list),NULL);
    new_list = malloc(new_size);
    if (new_list == NULL)
        return NULL;
    if (old_size < new_size)
        copy_size = old_size;
    else 
        copy_size = new_size;
    ft_memcpy(new_list, list, copy_size);
    free(list);
    return (new_list);
}
int	free_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y] != NULL)
	{
		free(matrix[y]);
		y++;
	}
	free(matrix);
	return (1);
}



char *ft_itoa(int num)
{
    char *str;
    int len;
    int temp;
    
    if(num == 0)
        len = 1;
    else
        len = 0;
    temp = num;
    while (temp > 0)
    {
        len++;
        temp /= 10;
    }
    str = malloc(len + 1);
    if (!str) return NULL;
    str[len] = '\0';
    while (len > 0)
    {
        str[--len] = (num % 10) + '0';
        num /= 10;
    }
    return str;
}
