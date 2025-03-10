/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenExtractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:52:06 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/10 18:06:31 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	parse_pipeline(char ***pipeline_tokens, size_t num_pipes,
	t_core_struct *core)
{
	size_t		i;
	bool		pipe_in;
	bool		pipe_out;

	i = 0;
	core->functions = malloc(sizeof(t_comand) * num_pipes);
	if (!core->functions)
		return ;
	while (i < num_pipes)
	{
		pipe_in = (i > 0);
		pipe_out = (i < num_pipes - 1);
		core->functions[i] = comand_write(pipeline_tokens[i], pipe_in, pipe_out,
				core);
		i++;
	}
}

char	***build_pipeline_tokens(char **matrix_split, size_t num_pipes)
{
	size_t	i;
	char	***pipeline_tokens;

	pipeline_tokens = malloc(sizeof(char **) * (num_pipes + 1));
	i = 0;
	while (i < num_pipes)
	{
		pipeline_tokens[i] = token_master(matrix_split[i], ' ');
		i++;
	}
	pipeline_tokens[num_pipes] = NULL;
	return (pipeline_tokens);
}

void	tokenize(t_core_struct *core)
{
	size_t	i;
	char	**matrix_split;
	char	***utils_matrix;

	i = 0;
	matrix_split = pipe_splitter(core->read.line);
	core->pipe.number = count_pipe(matrix_split);
	core->pipe_split = matrix_split;
	utils_matrix = build_pipeline_tokens(matrix_split, core->pipe.number);
	parse_pipeline(utils_matrix, core->pipe.number, core);
	//print_command(core->functions);
	while (i < core->pipe.number)
	{
		free(utils_matrix[i]);
		i++;
	}
	free(utils_matrix);
}
