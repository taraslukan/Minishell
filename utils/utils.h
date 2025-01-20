#ifndef UTILS_H
#define UTILS_H

// Standard libraries

// Project-specific headers
#include "../minishell.h"
#include "../structMinishell.h"


void    *ft_rlc(void *list, size_t old_size, size_t new_size);
int	    free_matrix(char **matrix);

#endif /* MINISHELL_H */