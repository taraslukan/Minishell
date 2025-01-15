#ifndef MINISHELL_H
#define MINISHELL_H

// Var

#define PIPE_STD_IN  "PIPE_STD_IN"
#define PIPE_STD_OUT  "PIPE_STD_OUT"

// Standard libraries
#include <stdio.h>    
#include <unistd.h>   
#include <limits.h>   
#include <string.h>
#include <stdlib.h>   
#include <stdbool.h>  

// Project-specific headers
#include "libft/libft.h"
#include "utils/utils.h"
#include "structMinishell.h"
#include "read/read.h"
#include "exv/exv.h"
#include "token/token.h"      

#endif /* MINISHELL_H */
