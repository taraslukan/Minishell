#include "read.h"

char *rdLine(char *prompt)
{
    return (readline(prompt));
}

char *build_std_prompt(char *prompt)
{
    char *step;
    step = ft_strjoin("Minishell: ", prompt);
    return(ft_strjoin(step, " ➜> "));
}
// int get_type(char *prompt)
// {

// }
void start_read(void)
{
    char *input;
    char cwd[PATH_MAX];
    //char *home;
    char *heredocinput;

    //home = getenv("HOME");
    //chdir(home);
    getcwd(cwd, sizeof(cwd));
    while (1)
    {
        input = rdLine(build_std_prompt(cwd));
        heredocinput = tl_check_heredoc(input);
        if (!heredocinput)
            test(input);
        else 
            test(heredocinput);
    }
    printf("\n %s \n", heredocinput);
    // printf("%s", input);
}
