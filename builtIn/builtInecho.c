/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtInecho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:35:03 by lukan             #+#    #+#             */
/*   Updated: 2025/01/20 14:36:57 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

bool is_option_n(const char *arg)
{
    int i = 1;

    if (arg[0] != '-') // Non inizia con "-"
        return false;

    while (arg[i] == 'n') // Controlla che siano solo 'n'
        i++;

    return (arg[i] == '\0'); // Deve terminare correttamente
}

// Rimuove le virgolette singole o doppie da una stringa
char *remove_quotes(const char *str)
{
    size_t len = strlen(str);
    char *result = malloc(len + 1); // Alloca memoria per la stringa senza virgolette
    size_t i = 0, j = 0;

    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '\"') // Salta le virgolette
        {
            result[j] = str[i];
            j++;
        }
        i++;
    }
    result[j] = '\0'; // Termina la stringa
    return result;
}

// Funzione principale ft_echo
void ft_echo(int argc, char **argv)
{
    bool newline = true; // Indica se stampare un newline alla fine
    int i = 1;

    // Controlla l'opzione -n
    if (i < argc && is_option_n(argv[i]))
    {
        newline = false; // Disabilita il newline
        i++;             // Salta l'opzione
    }

    // Processa e stampa i rimanenti argomenti
    while (i < argc + 1)
    {
        char *clean_arg = remove_quotes(argv[i]); // Rimuovi virgolette
        if (!clean_arg)
        {
            fprintf(stderr, "Memory allocation error\n");
            return;
        }
        printf("%s", clean_arg);
        free(clean_arg); // Libera la memoria temporanea
        i++;
        if (i < argc + 1) // Aggiungi uno spazio tra gli argomenti
            printf(" ");
    }

    if (newline) // Stampa un newline, se necessario
        printf("\n");
}