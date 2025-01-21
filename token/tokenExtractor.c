/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenExtractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:52:06 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/21 16:39:05 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// Nuova funzione per gestire i file di input/output e la modalità di append
static void handle_file_redirections(t_comand *ret, char **matrix, int i, bool pipe_in, bool pipe_out)
{
    if (pipe_in)
        ret->in_fd = ret->core->fd[0];
    else
        ret->in_fd = -1;
    if (pipe_out)
        ret->out_fd = ret->core->fd[1];
    else
        ret->out_fd = -1;
    ret->append = false;
    while (matrix[i])
    {
        if (strcmp(matrix[i], "<") == 0 && matrix[i + 1])
            ret->in_fd = open(matrix[++i], O_RDONLY);
        else if (strcmp(matrix[i], ">") == 0 && matrix[i + 1])
            ret->out_fd = open(matrix[++i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (strcmp(matrix[i], ">>") == 0 && matrix[i + 1])
        {
            ret->out_fd = open(matrix[++i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            ret->append = true;
        }
        i++;
    }
}
t_comand comand_write(char **matrix, bool pipe_in, bool pipe_out, t_coreStruct *core)
{
    t_comand ret;
    int i;
    int j;

    i = 0;
    j = 1;
    ret.exe = matrix[i++];
    int arg_count = 0;
    while (matrix[i] && strcmp(matrix[i], ">") && strcmp(matrix[i], "<") && strcmp(matrix[i], ">>"))
        arg_count++, i++;
    ret.args = malloc(sizeof(char *) * (arg_count + 1));
    ret.args[0] = ret.exe;
    while (j <= arg_count)
    {
        ret.args[j] = matrix[j];
        j++;
    }
    ret.argc = arg_count;
    ret.args[arg_count + 1] = NULL;
    ret.core = core;
    handle_file_redirections(&ret, matrix, i, pipe_in, pipe_out);
    return ret;
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
	char **matrix_split = pipe_splitter(core->imput);
	core->pipe.number = count_pipe(matrix_split);
	core->pipeSplit = matrix_split;
	char ***utils_matrix = build_pipeline_tokens(matrix_split, core->pipe.number);
	core->functions = parse_pipeline(utils_matrix, core->pipe.number, core);
	// print_functions(core);
	while (i < core->pipe.number)
	{
		free(utils_matrix[i]);
		i++;
	}
	free(utils_matrix);
}
