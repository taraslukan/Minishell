/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_builtIn_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:23:24 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/03 14:49:58 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

static char	**built_in_finder(void)
{
	static char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL // Terminatore dell'array
	};

	return (builtins);
}

void	execute_builtin(const t_comand *cmd)
{
	if (strcmp(cmd->exe, "echo") == 0)
		ft_echo(cmd->argc, cmd->args);
	else if (strcmp(cmd->exe, "cd") == 0)
		printf("cd \n");
	else if (strcmp(cmd->exe, "pwd") == 0)
		ft_pwd();
	else if (strcmp(cmd->exe, "export") == 0)
		printf("export");
	else if (strcmp(cmd->exe, "unset") == 0)
		printf("unset");
	else if (strcmp(cmd->exe, "env") == 0)
		print_env(cmd->core->env);
	else if (strcmp(cmd->exe, "exit") == 0)
		ft_exit(cmd->core);
}

bool	is_builtin(const char *cmd)
{
	int		i;
	char	**builtins;

	i = 0;
	builtins = built_in_finder();
	while (builtins[i])
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
