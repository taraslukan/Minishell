/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:40:05 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/05 14:42:50 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

extern int	g_last_exit_status;

typedef struct s_expander {
	char	*result;
	size_t	i;
	size_t	j;
	bool	in_single_quotes;
	bool	in_double_quotes; // Aggiungi questa variabile
}	t_expander;

void	append_exit_status(t_expander *exp)
{
	char	*buffer;
	int		len;

	buffer = ft_itoa(g_last_exit_status);
	if (!buffer)
		return ;
	len = ft_strlen(buffer);
	ft_strncpy(exp->result + exp->j, buffer, len);
	exp->j += len;
	free(buffer);
}

void	copy_var_name(char *line, t_expander *exp, char *var_name)
{
	size_t	start;
	size_t	len;

	start = ++(exp->i);
	while (line[exp->i] && (isalnum(line[exp->i]) || line[exp->i] == '_'))
		(exp->i)++;
	len = exp->i - start;
	if (len >= sizeof(var_name))
		return ;
	ft_strncpy(var_name, &line[start], len);
	var_name[len] = '\0';
}

void	append_env_variable(char *line, t_expander *exp)
{
	char	var_name[256];
	char	*var_value;
	size_t	value_len;

	copy_var_name(line, exp, var_name);
	var_value = getenv(var_name);
	if (var_value)
	{
		value_len = ft_strlen(var_value);
		ft_strncpy(exp->result + exp->j, var_value, value_len);
		exp->j += value_len;
	}
}

void	process_char(char *line, t_expander *exp)
{
	if (line[exp->i] == '\'' && !exp->in_double_quotes)
		exp->in_single_quotes = !exp->in_single_quotes;
	else if (line[exp->i] == '"' && !exp->in_single_quotes)
		exp->in_double_quotes = !exp->in_double_quotes;
	else if (line[exp->i] == '$' && !exp->in_single_quotes)
	{
		if (line[exp->i + 1] == '?')
		{
			append_exit_status(exp);
			exp->i += 1;
		}
		else
			append_env_variable(line, exp);
	}
	else
		exp->result[(exp->j)++] = line[exp->i];
	(exp->i)++;
}

char	*expand_variables(char *line, bool global_var_enable)
{
	t_expander	exp;
	char		*final_result;

	if (!line || !global_var_enable)
		return (strdup(line));
	exp.result = malloc(strlen(line) * 2 + 4096);
	if (!exp.result)
		return (NULL);
	exp.i = 0;
	exp.j = 0;
	exp.in_single_quotes = 0;
	exp.in_double_quotes = 0; // Inizializza la variabile
	while (line[exp.i])
		process_char(line, &exp);
	exp.result[exp.j] = '\0';
	final_result = ft_strdup(exp.result);
	free(exp.result);
	if (line)
		free(line);
	printf("FINAL RESULT: %s\n", final_result);
	return (final_result);
}