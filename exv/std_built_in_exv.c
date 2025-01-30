#include "exv.h"

extern char **environ;

void call_exe_func_built_in_std(t_exec_manager *tools)
{
	int         	status;
	pid_t       	pid;

	manage_pipe(tools);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{ 
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exe_func_built_in_std(tools);
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (waitpid(pid, &status, 0) == -1)
		exit(EXIT_FAILURE);
	manage_pipe_close_utils(tools);
}
void exe_func_built_in_std(t_exec_manager *tools)
{
    char *cmd;
    
    cmd = tools->cmd->exe;
    if (strcmp(cmd, "echo") == 0)
    {
        redirect_input(tools);
        redirect_output(tools);
        ft_echo(tools->cmd->argc, tools->cmd->args);
    }
    else if (strcmp(cmd, "pwd" ) == 0)
    {
        redirect_input(tools);
        redirect_output(tools);
        ft_pwd();
    }
    else if (strcmp(cmd, "env" ) == 0)
    {
        redirect_input(tools);
        redirect_output(tools);
        print_env(environ);
        
    }
    free(cmd);
}

void built_in_decision_menager(t_exec_manager *tools)
{
    char *cmd;
    
    cmd = tools->cmd->exe;
    if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "pwd" ) == 0 || strcmp(cmd, "env" ) == 0)
        call_exe_func_built_in_std(tools);
    else if (strcmp(cmd, "cd") == 0)
        ft_cd(tools->cmd->argc, tools->cmd->args);
    else if (strcmp(cmd, "export") == 0)
        printf("export");
    else if (strcmp(cmd, "unset") == 0)
        printf("unset");
    else if (strcmp(cmd, "exit") == 0)
        ft_exit();
    
    free(cmd);
}