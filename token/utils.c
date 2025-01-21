#include "token.h"

void print_functions( t_coreStruct *core)
{
    if (!core || !core->functions)
    {
        printf("No functions to display.\n");
        return;
    }

    printf("Number of commands: %zu\n", core->pipe.number);
    for (size_t i = 0; i < core->pipe.number; i++)
    {
        t_comand *cmd = &core->functions[i];
        printf("Command %zu:\n", i + 1);
        printf("  Executable: %s\n", cmd->exe ? cmd->exe : "(null)");

        // Stampa argomenti
        printf("  Arguments: |");
        if (cmd->args)
        {
            for (size_t j = 0; cmd->args[j]; j++)
                printf("%s\n             |", cmd->args[j]);
        }
        else
        {
            printf("(none)");
        }
        printf("\n");

        // Stampa file di input/output
        printf("  Input file: %d\n", cmd->in_fd);
        printf("  Output file: %d\n", cmd->out_fd);
        printf("  Append mode: %s\n", cmd->append ? "true" : "false");
        printf("\n");
    }
}
