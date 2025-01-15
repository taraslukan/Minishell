/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:08:28 by lukan             #+#    #+#             */
/*   Updated: 2025/01/15 17:09:35 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

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
    ft_strlcpy(ret, s + start, sub_len + 1);

    return (ret);
}

// Funzione per controllare il delimitatore
bool check_delimiter(const char *str, const char *delimiter)
{
    int len;
    int end;

    if (!str || !delimiter)												// Controllo di sicurezza
        return (false);

    len = ft_strlen(str);
    end = len - 1;

    if (end >= 0 && str[end] == '\n')									// Ignora il carattere \n finale, se presente
        end--;

    if (end >= 0 && str[end] == ' ')									// Controlla se ci sono spazi finali
        return (false);

    int start = end;													// Trova l'inizio dell'ultima parola
    while (start >= 0 && str[start] != ' ')
        start--;

    // Confronta l'ultima parola con il delimitatore
	return (ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0);

}


char	*save_delimiter(int i, char *input)
{
	int		start;
	int		len;
	char	*delimiter;

	start = i;
	while (input[i] && input[i] > ' ') // Trova la fine della parola
		i++;
	len = i - start;
	delimiter = ft_substr_tarl(input, start, len); // Salva il delimitatore
	return (delimiter);
}

char	*here_loop(char *delimiter)
{
	char	*line;
	char	*fullstring;
	char	*temp;

	fullstring = ft_strdup(""); // Inizializza fullstring come stringa vuota
	while (1)
	{
		line = readline("heredoc:(.y.) --> ");
		if (!line)
			break;
		// Verifica se la riga corrente è il delimitatore
		if (check_delimiter(line, delimiter))
		{
			free(line);
			break;
		}
		// Concatena la riga con '\n' alla stringa completa
		temp = fullstring;
		fullstring = ft_strjoin(fullstring, line);
		fullstring = ft_strjoin(fullstring, "\n");
		free(temp); // Libera la vecchia stringa concatenata
		free(line);
	}
	return (fullstring);
}


char	*tl_check_heredoc(char *input)
{
	int		i;
	char	*heredoc_pw;
	char	*heredocinput;
	
	if (!input)
		return (NULL);
	i = 0;
	heredoc_pw = NULL;
	heredocinput = NULL;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<') // Controlla il simbolo "<<"
		{
			i += 2;
			while (input[i] && input[i] <= ' ') // Salta gli spazi dopo "<<"
				i++;
			heredoc_pw = save_delimiter(i, input); // Salva il delimitatore
			heredocinput = here_loop(heredoc_pw);
			break;
		}
		i++;
	}
	//printf("\n%s \n", heredocinput);
	return (heredocinput); // Restituisce la stringa NON splittata per \n
}
