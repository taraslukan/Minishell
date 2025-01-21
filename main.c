#include "minishell.h" // Includi il tuo header con extern

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// void build_pipe_fd(t_coreStruct *core)
// {
//     // Apre il file per lettura e scrittura (se il file non esiste, viene creato)
//     core->fd[0] = open("pipe.txt", O_RDONLY);  // Apertura in lettura
//     core->fd[1] = open("pipe.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);  // Apertura in scrittura

//     if (core->fd[0] == -1 || core->fd[1] == -1)
//     {
//         perror("open fail");
//         exit(1);
//     }

//     // Verifica che i file descriptor siano stati correttamente aperti
//     printf("Lettura originale: %d | Scrittura originale %d\n", core->fd[0], core->fd[1]);

//     // Se necessario, puoi duplicare i file descriptor per conservarli
//     core->std_pipe_in = dup(core->fd[0]);
//     core->std_pipe_out = dup(core->fd[1]);

//     if (core->std_pipe_in == -1 || core->std_pipe_out == -1)
//     {
//         perror("dup fail");
//         exit(1);
//     }

//     // Se non sono più necessari, puoi chiudere i file descriptor originali
//     close(core->fd[0]);
//     close(core->fd[1]);

//     // I file descriptor duplicati rimangono aperti per l'uso futuro
// }


void build_pipe_fd(t_coreStruct *core)
{
    //int fd[2];

    if (pipe(core->fd) == -1)
    {
        perror("pipe fail");
        exit(1);
    }
    printf("Lettura originale: %d| Scrittura originale %d\n", core->fd[0], core->fd[1]);
    // core->std_pipe_in = dup(fd[0]);
    // core->std_pipe_out = dup(fd[1]);
    // //printf("Lettura cpy: %d| Scrittura cpy %d", core->std_pipe_in, core->std_pipe_out);
    // if (core->std_pipe_in == -1 || core->std_pipe_out == -1)
    // {
    //     perror("dup fail");
    //     exit(1);
    // }
    // close(fd[0]);
    // close(fd[1]);
}

void start_process(t_coreStruct *core)
{
    while (1)
    {
        core->imput = start_read();
        if (!core->imput)
            continue;

        build_pipe_fd(core);
        tokenize(core);
        std_exv(core);
        // close(core->fd[0]);
        // close(core->fd[1]);
        // close(core->std_pipe_in);
        // close(core->std_pipe_out);
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