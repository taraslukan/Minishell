#ifndef STRUCTMINISHELL_H
#define STRUCTMINISHELL_H

#include <stdbool.h>
#include <stddef.h> // Per `size_t`

typedef struct s_comand
{
    char    *exe;
    char    **args;
    char    *in_file;
    char    *out_file;
    bool    append;
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
} t_coreStruct;

#endif /* STRUCTMINISHELL_H */
