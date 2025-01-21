/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:55:52 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/21 14:25:14 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

void    ft_exit()
{
    exit(99);
}

// void ft_cd(int argc, char **argv)
// {
//     char    cwd[1024];
//     char    *oldpwd;
//     char    *path;
    
//     if (argc > 1)
//         return(printf("cd: string not in pwd: %s\n", path[1]));
//     ft_strlcpy(path ,argv[1], ft_strlen(argv[1]));
//     if (!path || ft_strcmp(path, "~") == 0)
//         path = getenv("HOME");

//     if (ft_strcmp(path, "-") == 0 || ft_strcmp(path, "..") == 0)
//         path = getenv("OLDPWD");
//     oldpwd = getcwd(NULL, 0);
//     if (chdir(path) == -1) {
//         fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
//         free(oldpwd);
//         return;
//     }
//     if (oldpwd)
//         setenv("OLDPWD", oldpwd, 1);
//     if (getcwd(cwd, sizeof(cwd)))
//         setenv("PWD", cwd, 1);
//     free(oldpwd);
// }

void    ft_pwd()
{
    char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
    printf("%s \n", cwd);
}