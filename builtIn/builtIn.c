/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:55:52 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/03 17:27:38 by fluzi            ###   ########.fr       */
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void ft_cd(int argc, char **argv)
{
    char cwd[1024];
    char *oldpwd;
    char *path;

    // Se non viene passato alcun argomento, usa la directory HOME
    if (argc < 2) {
        path = getenv("HOME");
        if (!path) {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    } else {
        path = argv[1];

        // Gestione speciale per "cd -": ritorna alla directory precedente
        if (strcmp(path, "-") == 0) {
            path = getenv("OLDPWD");
            if (!path) {
                fprintf(stderr, "cd: OLDPWD not set\n");
                return;
            }
            printf("%s\n", path); // Stampa la directory corrente prima di cambiarla
        }
    }

    // Salva la directory attuale in modo da aggiornare OLDPWD
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd) {
        perror("getcwd");
        return;
    }

    // Prova a cambiare directory
    if (chdir(path) == -1) {
        fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
        free(oldpwd);
        return;
    }

    // Aggiorna OLDPWD con la vecchia directory
    if (setenv("OLDPWD", oldpwd, 1) == -1) {
        perror("setenv OLDPWD");
        free(oldpwd);
        return;
    }
    free(oldpwd);

    // Aggiorna PWD con la nuova directory corrente
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return;
    }
    if (setenv("PWD", cwd, 1) == -1) {
        perror("setenv PWD");
        return;
    }
}



void    ft_pwd()
{
    char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
    printf("%s \n", cwd);
    exit(0);
}