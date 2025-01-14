/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_heredoc_msh.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:39:14 by lukan             #+#    #+#             */
/*   Updated: 2025/01/13 23:40:12 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_tarl(const char *s, unsigned int start, size_t len)
{
    char	*ret;
    size_t	s_len;
    size_t	sub_len;

    if (!s)
        return (NULL);

    s_len = ft_strlen(s);

    // Se `start` è fuori dalla stringa, ritorna una stringa vuota
    if (start >= s_len)
        return (ft_strdup(""));

    // Calcola la lunghezza effettiva della sottostringa
    sub_len = s_len - start;
    if (sub_len > len)
        sub_len = len;

    // Alloca memoria per la sottostringa
    ret = (char *)malloc(sizeof(char) * (sub_len + 1));
    if (!ret)
        return (NULL);

    // Copia i caratteri della sottostringa
    ft_strlcpy(ret, s + start, sub_len + 1);

    return (ret);
}