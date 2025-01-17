#include "minishell.h"

int main(void)
{

    char *path;

    path = getenv("OLDPWD");
    printf("%s", path);
}