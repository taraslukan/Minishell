#ifndef STRUCTMINISHELL_H
#define STRUCTMINISHELL_H

#include <stdbool.h>
#include <stddef.h> 

extern int g_last_exit_status;

typedef struct s_coreStruct t_coreStruct;

typedef struct s_read
{
    char    *std;
    char    *line;
    char    *in_file;
    char    *delimiter;
    bool    heredoc;
    bool    success;
    bool    global_var_enable;

} t_read;

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
    t_comand        *functions;
    t_pipeAdmin     pipe;
    t_read          read;
    char            *imput;
    char            **pipeSplit;
    char            **env;
    char            *path;
    int             stdin_copy;
    int             stdout_copy;
} t_coreStruct;

#endif /* STRUCTMINISHELL_H */
