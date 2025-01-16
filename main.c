#include "minishell.h"

// static void set_home(void)
// {
//     char *home;

//     home = getenv("HOME");
//     chdir(home);
// }
static void start_process(t_coreStruct *core)
{
    while(1)
    {
        core->imput = start_read();
        if (!core->imput)
            continue;
        tokenize(core);
        std_exv(&core->functions[0]);
        continue;
    }
}

int main(void)
{
    t_coreStruct    core;

    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, handle_sigtstp);
    signal(SIGQUIT, SIG_IGN);
    
    core.env = copy_env();
    start_process(&core);
    return (0);
}