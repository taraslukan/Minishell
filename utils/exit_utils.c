/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:08:59 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/03 15:06:50 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	free_matrix_utils(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			if (matrix[i])
			{
				free(matrix[i]);
				matrix[i] = NULL;
			}
			i++;
		}
		free(matrix);
	}
}

static void	free_comand(t_comand *comand)
{
	if (comand)
	{
		if (comand->exe)
		{
			free(comand->exe);
			comand->exe = NULL;
		}
		if (comand->in_file)
		{
			free(comand->in_file);
			comand->in_file = NULL;
		}
		if (comand->out_file)
		{
			free(comand->out_file);
			comand->out_file = NULL;
		}
		free_matrix_utils(comand->args);
		if (comand->core)
		{
			free(comand->core);
			comand->core = NULL;
		}
	}
}

void	safe_exit(t_core_struct *core, int exit_status)
{
	if (core->read.std)
	{
		free(core->read.std);
		core->read.std = NULL;
	}
	if (core->read.line)
	{
		free(core->read.line);
		core->read.line = NULL;
	}
	if (core->read.in_file)
	{
		free(core->read.in_file);
		core->read.in_file = NULL;
	}
	if (core->read.delimiter)
	{
		free(core->read.delimiter);
		core->read.delimiter = NULL;
	}
	free_matrix_utils(core->pipe_split);
	free_matrix_utils(core->env);
	free_comand(core->functions);
	exit(exit_status);
}
