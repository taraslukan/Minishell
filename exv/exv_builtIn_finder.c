/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_builtIn_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:23:24 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/15 17:06:42 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

static char **built_in_finder()
{
    char **builtins = malloc(sizeof(char *) * 8);
    builtins[0] = "echo";
    builtins[1] = "cd";
    builtins[2] = "pwd";
    builtins[3] = "export";
    builtins[4] = "unset";
    builtins[5] = "env";
    builtins[6] = "exit";
    builtins[7] = NULL;
    return (builtins);
}

// void execute_builtin(const t_comand *cmd)
// {
//     if (strcmp(cmd->exe, "echo") == 0) {
//         // Implementazione di echo
//     } else if (strcmp(cmd->exe, "cd") == 0) {
//         // Implementazione di cd
//     } else if (strcmp(cmd->exe, "pwd") == 0) {
//         // Implementazione di pwd
//     } else if (strcmp(cmd->exe, "export") == 0) {
//         // Implementazione di export
//     } else if (strcmp(cmd->exe, "unset") == 0) {
//         // Implementazione di unset
//     } else if (strcmp(cmd->exe, "env") == 0) {
//         // Implementazione di env
//     } else if (strcmp(cmd->exe, "exit") == 0) {
//         // Implementazione di exit
//     }
// }
bool is_builtin(const char *cmd)
{
    int i;
    char **builtins;

    i = 0;
    builtins = built_in_finder();
    while (builtins[i])
    {
        if (strcmp(cmd, builtins[i]) == 0)
            return true;
        i++;
    }
    return false;
}
