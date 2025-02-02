#ifndef READ_H
#define READ_H


#include "../minishell.h"
#include "../structMinishell.h"
#include <readline/history.h>
#include <readline/readline.h>


char    *build_std_prompt();
void    find_heredoc(t_read *r_tools);

//Utils
char    *remove_heredoc(const char *input);
char    *extract_delimiter(char *start, char *end);
char    *find_heredoc_delimiter(char *start);
char    *skip_spaces(char *start);
char    *find_heredoc_start(char *line);

//heredoc menage
void    create_file(t_read *r_tools);
void    write_file(t_read *r_tools, char *heredoc_line);


void    std_read(t_read *r_tools);
void    std_here_doc(t_read *r_tools);

bool    is_history(char *line);


#endif /* READ_H */