/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:55:52 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/30 17:42:02 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

void    ft_exit()
{
    exit(99);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void ft_cd(int argc, char **argv)
{
    char cwd[1024];
    char *oldpwd;
    char *path;

    if (argc < 2) {
        path = getenv("HOME");
        if (!path) {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    } else {
        path = argv[1];

        // Gestione speciale per "cd -"
        if (strcmp(path, "-") == 0) {
            path = getenv("OLDPWD");
            if (!path) {
                fprintf(stderr, "cd: OLDPWD not set\n");
                return;
            }
            printf("%s\n", path); // Stampa la directory prima di cambiarla
        }
    }

    // Salva la directory attuale
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd) {
        perror("getcwd");
        return;
    }

    // Cambia directory
    if (chdir(path) == -1) {
        fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
        free(oldpwd);
        return;
    }

    // Aggiorna le variabili d'ambiente
    setenv("OLDPWD", oldpwd, 1);
    if (getcwd(cwd, sizeof(cwd)))
        setenv("PWD", cwd, 1);

    free(oldpwd);
}


void    ft_pwd()
{
    char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
    printf("%s \n", cwd);
    exit(0);
}