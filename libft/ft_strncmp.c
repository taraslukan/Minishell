/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:28:43 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/13 17:00:40 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h> // Necessario per il tipo size_t

/**
 * ft_strncmp - Confronta due stringhe fino a un massimo di `n` caratteri.
 * @s1: La prima stringa da confrontare.
 * @s2: La seconda stringa da confrontare.
 * @n: Il numero massimo di caratteri da confrontare.
 * 
 * Ritorna:
 *  - Un valore < 0 se s1 < s2.
 *  - Un valore > 0 se s1 > s2.
 *  - 0 se le stringhe sono uguali fino a `n` caratteri o se `n` è 0.
 */
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    if (n == 0)
        return (0);

    i = 0;
    while (i < n && s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }

    // Se il ciclo è terminato, confrontiamo un eventuale carattere finale
    if (i < n)
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);

    return (0);
}
