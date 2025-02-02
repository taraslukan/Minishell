/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menage_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:40:40 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/31 17:30:09 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

static char *name_finder(char *candidate)
{
    char *name = strdup(candidate); 
    char *temp;
    char *number;
    int i = 0;

    while (access(name, F_OK) == 0)
    {
        number = ft_itoa(i++);
        temp = ft_strjoin(candidate, number);
        free(name);
        name = temp;
        free(number);
    }
    return name;
}

void write_file(t_read *r_tools, char *heredoc_line)
{
    int fd = open(r_tools->in_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Errore nell'aprire il file");
        return;
    }
    write(fd, heredoc_line, strlen(heredoc_line));
    write(fd, "\n", 1);
    close(fd);
}


void    create_file(t_read *r_tools)
{
    int fd;

    r_tools->in_file = name_finder("heredoc_std");
    fd = open(r_tools->in_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Errore nell'aprire o creare il file");
        return;
    }
    close(fd);
}