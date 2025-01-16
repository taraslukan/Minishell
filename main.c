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
    
    core.env = copy_env();
    start_process(&core);
    return (0);
}