#ifndef STRUCTMINISHELL_H
#define STRUCTMINISHELL_H

#include <stdbool.h>
#include <stddef.h> // Per `size_t`

typedef struct s_coreStruct t_coreStruct;

typedef struct s_comand
{
    char            *exe;
    int             argc;
    char            **args;
    char            *in_file;
    char            *out_file;
    bool            append;
    t_coreStruct    *core;
} t_comand;

typedef struct s_pipeAdmin
{
    bool    exists;
    size_t  number;
} t_pipeAdmin;

typedef struct s_coreStruct
{
    t_comand    *functions;
    t_pipeAdmin pipe;
    char        **pipeSplit;
    char        **env;
    char        *imput;
    char        *path;
    int         stdin_copy;
    int         stdout_copy;
    int         std_pipe_in;
    int         std_pipe_out;
    int         fd[2];
} t_coreStruct;



#endif /* STRUCTMINISHELL_H */
