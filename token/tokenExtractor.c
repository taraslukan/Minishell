/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenExtractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:52:06 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/02 17:10:11 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"


static void handle_file_redirections(t_comand *ret, char **matrix, int i, bool pipe_in, bool pipe_out)
{
	if(ret->core->read.heredoc )
		ret->in_file = ret->core->read.in_file;
    if (pipe_in)
        ret->in_file = PIPE_STD_IN;
    else if (!ret->core->read.heredoc && !pipe_in)
        ret->in_file = NULL;
    if (pipe_out)
        ret->out_file = PIPE_STD_OUT;
    else 
        ret->out_file = NULL;
    ret->append = false;
    while (matrix[i])
    {
        if (strcmp(matrix[i], "<") == 0 && matrix[i + 1])
            ret->in_file = matrix[++i];
        else if (strcmp(matrix[i], ">") == 0 && matrix[i + 1])
            ret->out_file = matrix[++i];
        else if (strcmp(matrix[i], ">>") == 0 && matrix[i + 1])
        {
            ret->out_file = matrix[++i];
            ret->append = true;
        }
        i++;
    }
}

t_comand comand_write(char **matrix, bool pipe_in, bool pipe_out, t_coreStruct *core)
{
	t_comand ret;
	int i = 0, arg_count = 0;

	while (matrix[i]) 
	{
		if (!strcmp(matrix[i], ">") || !strcmp(matrix[i], "<") || !strcmp(matrix[i], ">>"))
			i += 2;
		else
		{
			arg_count++;
			i++;
		}
	}
	ret.args = malloc(sizeof(char *) * (arg_count + 1));
	if (!ret.args)
		return (ret);
	int j = 0, k = 0;
	while (matrix[j]) 
	{
		if (!strcmp(matrix[j], ">") || !strcmp(matrix[j], "<") || !strcmp(matrix[j], ">>"))
			j += 2;
		else
			ret.args[k++] = matrix[j++];
	}
	ret.exe = ret.args[0];
	ret.args[k] = NULL;
	ret.argc = arg_count;
	ret.core = core;
	handle_file_redirections(&ret, matrix, 0, pipe_in, pipe_out);
	return (ret);
}

t_comand *parse_pipeline(char ***pipeline_tokens, size_t num_pipes, t_coreStruct *core)
{
	t_comand *commands;
	size_t i;

	i = 0;
	commands = malloc(sizeof(t_comand) * num_pipes);
	if (!commands)
		return NULL;
	while (i < num_pipes)
	{
		bool pipe_in = (i > 0);
		bool pipe_out = (i < num_pipes - 1);
		commands[i] = comand_write(pipeline_tokens[i], pipe_in, pipe_out, core);
		i++;
	}
	return commands;
}

char ***build_pipeline_tokens(char **matrix_split, size_t num_pipes)
{
	size_t i;
	char ***pipeline_tokens;

	pipeline_tokens = malloc(sizeof(char **) * (num_pipes + 1));
	i = 0;
	while (i < num_pipes)
	{
		pipeline_tokens[i] = token_master(matrix_split[i], ' ');
		i++;
	}
	pipeline_tokens[num_pipes] = NULL;
	return pipeline_tokens;
}

void tokenize(t_coreStruct *core)
{
	size_t i;

	i = 0;
	char **matrix_split = pipe_splitter(core->read.line);
	core->pipe.number = count_pipe(matrix_split);
	core->pipeSplit = matrix_split;
	char ***utils_matrix = build_pipeline_tokens(matrix_split, core->pipe.number);
	core->functions = parse_pipeline(utils_matrix, core->pipe.number, core);
	//print_functions(core);  
	while (i < core->pipe.number)
	{
		free(utils_matrix[i]);
		i++;
	}
	free(utils_matrix);
}
