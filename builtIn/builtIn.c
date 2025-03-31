/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:55:52 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 13:53:01 by fluzi            ###   ########.fr       */
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

int	update_pwd(char ***env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (0);
	}
	if (set_env_value(env, "PWD", cwd) == -1)
	{
		perror("setenv PWD");
		return (0);
	}
	return (1);
}

int	update_oldpwd(char ***env, char *oldpwd)
{
	if (set_env_value(env, "OLDPWD", oldpwd) == -1)
	{
		perror("setenv OLDPWD");
		return (0);
	}
	return (1);
}

void	ft_cd(int argc, char **argv, char ***env)
{
	char	*oldpwd;
	char	*path;

	oldpwd = getcwd(NULL, 0);
	path = get_target_path(argc, argv);
	if (!path)
		return ;
	if (!oldpwd)
		return (NULL, perror("getcwd"));
	if (chdir(path) == -1)
	{
		fprintf(stderr, "cd: %s: \n", path);
		free(oldpwd);
		return ;
	}
	if (!update_oldpwd(env, oldpwd))
	{
		free(oldpwd);
		return ;
	}
	free(oldpwd);
	if (!update_pwd(env))
		return ;
}

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s \n", cwd);
	exit(0);
}
