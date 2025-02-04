/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:43:23 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/04 12:49:49 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_last_exit_status;

void print_read(t_read *r_tools)
{
    if (!r_tools)
    {
        printf("t_read is NULL\n");
        return;
    }

    printf("Standard Line: %s\n", r_tools->std ? r_tools->std : "(NULL)");
    printf("Line: %s\n", r_tools->line ? r_tools->line : "(NULL)");
    printf("Input File: %s\n", r_tools->in_file ? r_tools->in_file : "(NULL)");
    printf("Delimiter: %s\n", r_tools->delimiter ? r_tools->delimiter : "(NULL)");
    printf("Heredoc: %s\n", r_tools->heredoc ? "true" : "false");
    printf("Success: %s\n", r_tools->success ? "true" : "false");
    printf("Var enable: %s\n", r_tools->global_var_enable ? "true" : "false");
}

void start_process(t_coreStruct *core)
{
    std_read(&core->read);
    if (strcmp(core->read.line, "") == 0)
       return;
    //print_read(&core->read);
    tokenize(core);
    std_exv(core);
    if(core->read.heredoc)
        unlink(core->read.in_file);
}

static void fork_builde(t_coreStruct *core)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    while (1)
        start_process(core);
}

void std_directory_save(t_coreStruct *core)
{
    core->stdin_copy = dup(STDIN_FILENO);
    if (core->stdin_copy == -1)
    {
        perror("dup stdin");
        exit(EXIT_FAILURE);
    }
    core->stdout_copy = dup(STDOUT_FILENO);
    if (core->stdout_copy == -1)
    {
        perror("dup stdout");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    t_coreStruct core;
    core.env = copy_env();
    std_directory_save(&core);
    fork_builde(&core);
    printf("\n exit %d: \n", g_last_exit_status);
    return (0);
}
