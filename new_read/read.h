/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:19:00 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/26 14:52:18 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "../minishell.h"
# include "../structMinishell.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_expander
{
	char	*result;
	size_t	i;
	size_t	j;
	int		in_single_quotes;
}	t_expander;

char	*build_std_prompt(void);
void	find_heredoc(t_read *r_tools);
char	*remove_heredoc(const char *input);
char	*extract_delimiter(char *start, char *end);
char	*find_heredoc_delimiter(char *start);
char	*skip_spaces(char *start);
char	*find_heredoc_start(char *line);
void	create_file(t_read *r_tools);
void	write_file(t_read *r_tools, char *heredoc_line);
void	std_read(t_read *r_tools);
void	std_here_doc(t_read *r_tools);
bool	is_history(char *line);
char	*expand_variables(char *line, bool global_var_enable);

#endif