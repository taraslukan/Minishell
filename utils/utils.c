/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:32:07 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/15 18:38:10 by fluzi            ###   ########.fr       */
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
