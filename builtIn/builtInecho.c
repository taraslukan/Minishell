/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtInecho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:35:03 by lukan             #+#    #+#             */
/*   Updated: 2025/01/30 15:29:52 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

bool is_option_n(const char *arg)
{
    int i = 1;

    if (arg[0] != '-')
        return false;

    while (arg[i] == 'n')
        i++;
    return (arg[i] == '\0');
}

char *remove_quotes(const char *str)
{
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    size_t i = 0, j = 0;

    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '\"')
        {
            result[j] = str[i];
            j++;
        }
        i++;
    }
    result[j] = '\0';
    return result;
}

void ft_echo(int argc, char **argv)
{
    bool newline = true;
    int i = 1;

    if (i < argc && is_option_n(argv[i]))
    {
        newline = false;
        i++;
    }
    while (i < argc + 1)
    {
        char *clean_arg = remove_quotes(argv[i]);
        if (!clean_arg)
        {
            fprintf(stderr, "Memory allocation error\n");
            return;
        }
        printf("%s", clean_arg);
        free(clean_arg);
        i++;
        if (i < argc + 1)
            printf(" ");
    }
    if (newline)
        printf("\n");
    exit(0);
}