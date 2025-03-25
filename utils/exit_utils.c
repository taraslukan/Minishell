/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:08:59 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/25 16:04:54 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	free_matrix_utils(char **matrix, size_t number)
{
	size_t	i;

	i = 0;
	if (matrix)
	{
		while (i < number)
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
	(void) comand;
	
	// if (comand)
	// {
	// 	if (comand->exe)
	// 	{
	// 		free(comand->exe);
	// 		comand->exe = NULL;
	// 	}
	// 	if (comand->in_file)
	// 	{
	// 		free(comand->in_file);
	// 		comand->in_file = NULL;
	// 	}
	// 	if (comand->out_file)
	// 	{
	// 		free(comand->out_file);
	// 		comand->out_file = NULL;
	// 	}
	// }
}

void	safe_exit(t_core_struct *core, int exit_status)
{
	free(core->read.std);
	free(core->read.line);
	free(core->read.in_file);
	free(core->read.delimiter);
	core->read.delimiter = NULL;
	free_matrix_utils(core->pipe_split, core->pipe.number);
	free_comand(core->functions);
	exit(exit_status);
}

void	free_struct(t_read *r_tools)
{
	if (r_tools)
	{
		if (r_tools->std)
			free(r_tools->std);
		if (r_tools->line)
			free(r_tools->line);
		if (r_tools->in_file)
			free(r_tools->in_file);
		if (r_tools->delimiter)
			free(r_tools->delimiter);
	}
}