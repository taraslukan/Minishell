#ifndef READ_H
#define READ_H


#include "../minishell.h"
#include <readline/history.h>
#include <readline/readline.h>


void	start_read(void);
char	*tl_check_heredoc(char *input);
char	*save_delimiter(int i, char *input);


#endif /* READ_H */