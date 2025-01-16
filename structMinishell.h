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
} t_coreStruct;

#endif /* STRUCTMINISHELL_H */
