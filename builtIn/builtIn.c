/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:55:52 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/05 15:27:56 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtIn.h"

char	*get_target_path(int argc, char **argv)
{
	char	*path;

	if (argc < 2)
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
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
				return (NULL);
			}
		}
	}
	return (path);
}

int	update_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (0);
	}
	if (setenv("PWD", cwd, 1) == -1)
	{
		perror("setenv PWD");
		return (0);
	}
	return (1);
}

int	update_oldpwd(char *oldpwd)
{
	if (setenv("OLDPWD", oldpwd, 1) == -1)
	{
		perror("setenv OLDPWD");
		return (0);
	}
	return (1);
}

void	ft_cd(int argc, char **argv)
{
	char	*oldpwd;
	char	*path;

	path = get_target_path(argc, argv);
	if (!path)
		return ;
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
	if (!update_oldpwd(oldpwd))
	{
		free(oldpwd);
		return ;
	}
	free(oldpwd);
	if (!update_pwd())
		return ;
}

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s \n", cwd);
	exit(0);
}
