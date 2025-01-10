/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:06:19 by fluzi             #+#    #+#             */
/*   Updated: 2024/01/17 15:06:34 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_isalnum(int str)
{
	if (ft_isalpha(str) == 1)
		return (1);
	else if (ft_isdigit(str) == 1)
		return (1);
	else
		return (0);
}