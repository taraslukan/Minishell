/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:53:22 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/14 13:11:46 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0) // Se la lunghezza da confrontare è zero, non ci sono differenze
		return (0);

	i = 0;
	while (i < n && s1[i] && s2[i]) // Confronta i caratteri finché sono uguali o fino al limite
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}

	// Se il ciclo si ferma prima di "n", controlla il carattere successivo
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);

	return (0);
}
