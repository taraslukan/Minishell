#include "token.h"

void print_functions( t_core_struct *core)
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
		printf("  Input file: %s\n", cmd->in_file);
		printf("  Output file: %s\n", cmd->out_file);
		printf("  Append mode: %s\n", cmd->append ? "true" : "false");
		printf("\n");
	}
}

void print_command(const t_comand *cmd) {
	if (!cmd) {
		printf("No command to display.\n");
		return;
	}

	printf("Command:\n");
	printf("  Executable: %s\n", cmd->exe ? cmd->exe : "(null)");

	printf("  Arguments: |");
	if (cmd->args) {
		for (size_t j = 0; cmd->args[j]; j++) {
			printf("%s\n             |", cmd->args[j]);
		}
	} else {
		printf("(none)");
	}
	printf("\n");

	printf("  Input file: %s\n", cmd->in_file ? cmd->in_file : "(null)");
	printf("  Output file: %s\n", cmd->out_file ? cmd->out_file : "(null)");
	printf("  Append mode: %s\n", cmd->append ? "true" : "false");
	printf("\n");
}
