/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenExtractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:52:06 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/15 17:08:52 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// Nuova funzione per gestire i file di input/output e la modalità di append
static void handle_file_redirections(t_comand *ret, char **matrix, int i, bool pipe_in, bool pipe_out)
{
	if (pipe_in)
		ret->in_file = PIPE_STD_IN;
	else 
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
// Funzione principale modificata
t_comand comand_write(char **matrix, bool pipe_in, bool pipe_out)
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
	ret.args[arg_count + 1] = NULL;
	handle_file_redirections(&ret, matrix, i, pipe_in, pipe_out);
	return ret;
}


t_comand *parse_pipeline(char ***pipeline_tokens, size_t num_pipes)
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
		commands[i] = comand_write(pipeline_tokens[i], pipe_in, pipe_out);
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

t_coreStruct tokenize(char *input)
{
	t_coreStruct principale;
	size_t i;

	i = 0;
	char **matrix_split = pipe_splitter(input);
	principale.pipe.number = count_pipe(matrix_split);
	principale.pipeSplit = matrix_split;
	char ***utils_matrix = build_pipeline_tokens(matrix_split, principale.pipe.number);
	principale.functions = parse_pipeline(utils_matrix, principale.pipe.number);
	//print_functions(&principale);
	while (i < principale.pipe.number)
	{
		free(utils_matrix[i]);
		i++;
	}
	
	free(utils_matrix);
	return(principale);
}

int test(char *input)
{
	// char *input = "ls -l 'file with spaces' | grep \"pattern\" > output.txt";
	t_coreStruct principale = tokenize(input); 
	std_exv(&principale.functions[0]);
	return 0;
}
