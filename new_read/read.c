/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:20:53 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/04 15:18:29 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

void	find_heredoc_type(t_read *r_tools)
{
	int		length;
	char	*new_delimiter;

	if (!r_tools || !r_tools->delimiter)
		return ;
	length = strlen(r_tools->delimiter);
	if (length >= 2
		&& (r_tools->delimiter[0] == '\''
			|| r_tools->delimiter[0] == '\"'
			|| r_tools->delimiter[0] == '`')
		&& (r_tools->delimiter[length - 1] == '\''
			|| r_tools->delimiter[length - 1] == '\"'
			|| r_tools->delimiter[length - 1] == '`'))
	{
		r_tools->global_var_enable = false;
		new_delimiter = ft_strndup(r_tools->delimiter + 1, length - 2);
		if (!new_delimiter)
			return ;
		free(r_tools->delimiter);
		r_tools->delimiter = new_delimiter;
	}
}

void	find_heredoc(t_read *r_tools)
{
	char	*start;
	char	*end;
	char	*new_str;

	if (!r_tools || !r_tools->line)
		return ;
	start = find_heredoc_start(r_tools->line);
	if (!start)
	{
		r_tools->heredoc = false;
		return ;
	}
	start += 2;
	start = skip_spaces(start);
	end = find_heredoc_delimiter(start);
	r_tools->delimiter = extract_delimiter(start, end);
	find_heredoc_type(r_tools);
	if (!r_tools->delimiter)
		return ;
	new_str = remove_heredoc(r_tools->line);
	if (!new_str)
		return ;
	free(r_tools->line);
	r_tools->line = new_str;
	r_tools->heredoc = true;
}

void	std_here_doc(t_read *r_tools)
{
	char	*heredoc_line;

	create_file(r_tools);
	while (1)
	{
		heredoc_line = readline("heredoc> ");
		if (strcmp(heredoc_line, r_tools->delimiter) == 0)
			break ;
		heredoc_line = expand_variables(heredoc_line,
				r_tools->global_var_enable);
		write_file(r_tools, heredoc_line);
		free(heredoc_line);
	}
}

void	set_struct(t_read *r_tools)
{
	if (!r_tools)
		return ;
	r_tools->std = ft_strdup("");
	r_tools->line = ft_strdup("");
	r_tools->in_file = ft_strdup("");
	r_tools->delimiter = ft_strdup("");
	r_tools->global_var_enable = true;
	r_tools->heredoc = false;
	r_tools->success = false;
	if (!r_tools->std || !r_tools->line || !r_tools->in_file
		|| !r_tools->delimiter)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
}

void	std_read(t_read *r_tools)
{
	char	*prompt;

	if (!r_tools)
		return ;
	set_struct(r_tools);
	prompt = build_std_prompt();
	r_tools->line = readline(prompt);
	if (!r_tools->line)
	{
		r_tools->success = false;
		return ;
	}
	add_history(r_tools->line);
	find_heredoc(r_tools);
	if (r_tools->heredoc)
		std_here_doc(r_tools);
	free(prompt);
	r_tools->line = expand_variables(r_tools->line, r_tools->global_var_enable);
}
