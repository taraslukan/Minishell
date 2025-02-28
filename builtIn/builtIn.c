/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:55:52 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/19 17:28:05 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

void	ft_exit(void)
{
	exit(99);
}

void	ft_cd(int argc, char **argv)
{
	char	cwd[1024];
	char	*oldpwd;
	char	*path;

	if (argc < 2)
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return ;
		}
	}
	else
	{
		path = argv[1];
		if (strcmp(path, "-") == 0)
		{
			path = getenv("OLDPWD");
			if (!path)
			{
				fprintf(stderr, "cd: OLDPWD not set\n");
				return ;
			}
			printf("%s\n", path);
		}
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		return ;
	}
	if (chdir(path) == -1)
	{
		fprintf(stderr, "cd: %s: \n", path);
		free(oldpwd);
		return ;
	}
	if (setenv("OLDPWD", oldpwd, 1) == -1)
	{
		perror("setenv OLDPWD");
		free(oldpwd);
		return ;
	}
	free(oldpwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	if (setenv("PWD", cwd, 1) == -1)
	{
		perror("setenv PWD");
		return ;
	}
}

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s \n", cwd);
	exit(0);
}
