/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:25:44 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/15 18:42:09 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
    unsigned char   *d;
    const unsigned char *s;

	i = 0;
    d = (unsigned char *)dst;
    s = (const unsigned char *)src;
	while (i < n)
		d[i] = s[i++];
    return (dst);
}
