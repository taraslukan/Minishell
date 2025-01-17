#include "minishell.h"  // Includi il tuo header con extern
pid_t pid = -1;         // Definisci la variabile globale


// static void set_home(void)
// {
//     char *home;

//     home = getenv("HOME");
//     chdir(home);
// }
static void start_process(t_coreStruct *core)
{
    while (1)
    {
        core->imput = start_read();
        if (!core->imput)
            continue;
        tokenize(core);
        std_exv(&core->functions[0]);
        continue;
    }
}

static void fork_builde(t_coreStruct *core)
{
    int     status;
    
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    while (1) {
        pid = fork();
        if (pid == -1) 
            continue; 
        if (pid == 0) {
            signal(SIGINT, handle_sigint);
            signal(SIGTSTP, handle_sigtstp);
            signal(SIGQUIT, SIG_IGN);
            start_process(core);
        } else { 
            waitpid(pid, &status, 0);
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 99) 
                exit(0);
        }
    }
}

int main(void)
{
    t_coreStruct core;

    core.env = copy_env();
    fork_builde(&core);
    return (0);
}