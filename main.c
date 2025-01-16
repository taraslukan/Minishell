#include "minishell.h"

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
    int         status;

    // Esegui il ciclo per rilanciare la funzione solo se necessario
    while (1) {
        pid = fork();
        if (pid == -1) {
            perror("Errore nella fork");
            continue; // Ripeti il fork in caso di errore
        }

        if (pid == 0) {  // Processo figlio
            signal(SIGINT, handle_sigint);  // Gestore per SIGINT
            signal(SIGTSTP, handle_sigtstp);
            signal(SIGQUIT, SIG_IGN);
            start_process(core);  // Avvia il processo figlio
        } else {  // Processo padre
            waitpid(pid, &status, 0);
            if (WIFSIGNALED(status)) {
                // Il processo figlio è stato terminato, rilancia la fork
                continue;
            }
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