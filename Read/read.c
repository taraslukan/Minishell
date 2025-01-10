#include "read.h"

char *rdLine(char *prompt)
{
    return (readline(prompt));
}

char build_std_prompt(char *promt)
{
    
}
void start_read(void)
{
    char *input;

    char cwd[PATH_MAX];

    getcwd(cwd, sizeof(cwd));
    input = rdLine(cwd);
    printf("%s", input);
}