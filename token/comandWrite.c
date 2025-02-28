/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comandWrite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:54:23 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/28 15:54:40 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	handle_file_redirections(t_comand *ret, char **matrix,
t_token_utils *t)
{
	if (ret->core->read.heredoc)
		ret->in_file = ret->core->read.in_file;
	if (t->pipe_in)
		ret->in_file = PIPE_STD_IN;
	else if (!ret->core->read.heredoc && !t->pipe_in)
		ret->in_file = NULL;
	if (t->pipe_out)
		ret->out_file = PIPE_STD_OUT;
	else
		ret->out_file = NULL;
	while (matrix[t->index])
	{
		ret->append = false;
		if (strcmp(matrix[t->index], "<") == 0 && matrix[t->index + 1])
			ret->in_file = matrix[++t->index];
		else if (strcmp(matrix[t->index], ">") == 0 && matrix[t->index + 1])
			ret->out_file = matrix[++t->index];
		else if (strcmp(matrix[t->index], ">>") == 0 && matrix[t->index + 1])
		{
			ret->out_file = matrix[++t->index];
			ret->append = true;
		}
		else
			t->index++;
	}
}

static void	utilscmdwrite(char **matrix, t_comand *ret, t_token_utils *tstr,
t_core_struct *core)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (matrix[j])
	{
		if (!strcmp(matrix[j], ">")
			|| !strcmp(matrix[j], "<") || !strcmp(matrix[j], ">>"))
			j += 2;
		else
			ret->args[k++] = matrix[j++];
	}
	ret->exe = ret->args[0];
	ret->args[k] = NULL;
	ret->argc = tstr->arg_count;
	ret->core = core;
	handle_file_redirections(ret, matrix, tstr);
}

t_comand	comand_write(char **matrix, bool pipe_in, bool pipe_out,
t_core_struct *core)
{
	t_comand		ret;
	int				i;
	t_token_utils	tstr;

	i = 0;
	tstr.arg_count = 0;
	while (matrix[i])
	{
		if (!strcmp(matrix[i], ">") || !strcmp(matrix[i], "<")
			|| !strcmp(matrix[i], ">>"))
			i += 2;
		else
		{
			tstr.arg_count++;
			i++;
		}
	}
	ret.args = malloc(sizeof(char *) * (tstr.arg_count + 1));
	if (!ret.args)
		return (ret);
	tstr.index = 0;
	tstr.pipe_in = pipe_in;
	tstr.pipe_out = pipe_out;
	utilscmdwrite(matrix, &ret, &tstr, core);
	return (ret);
}
