#include "minishell.h" // Includi il tuo header con extern

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



void start_process(t_coreStruct *core)
{
    while (1)
    {
        core->imput = start_read();
        if (!core->imput)
            continue;

        tokenize(core);
        std_exv(core);
        break;
    }
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
    return (0);
}