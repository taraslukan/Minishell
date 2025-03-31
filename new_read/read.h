/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:19:00 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 12:54:49 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "../minishell.h"
# include "../structMinishell.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_exp_var
{
	size_t		i;
	size_t		j;
	size_t		var_len;
	size_t		var_start;
	char		*result;
	char		*var_name;
	char		*var_value;
	char		*exit_str;
	bool		status_quote;
}	t_exp_var;

char	*build_std_prompt(void);
void	find_heredoc(t_read *r_tools);
char	*remove_heredoc(const char *input);
char	*extract_delimiter(char *start, char *end);
char	*find_heredoc_delimiter(char *start);
char	*skip_spaces(char *start);
char	*find_heredoc_start(char *line);
void	create_file(t_read *r_tools);
void	write_file(t_read *r_tools, char *heredoc_line);
void	std_read(char **env, t_read *r_tools);
void	std_here_doc(char **env, t_read *r_tools);
bool	is_history(char *line);
char	*expand_variables(char *line, bool global_var_enable,
			bool allow_expansion);
void	apic(t_exp_var *exp, char *line);
void	free_read(t_exp_var *exp);
void	copy_g_status(t_exp_var *exp);

#endif