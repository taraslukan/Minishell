#include "minishell.h"

int main(void)
{

    char *path;

    path = getenv("PATH");
    printf("%s\n", path);
    return(2);
}