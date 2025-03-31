/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:58:34 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 13:40:05 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

static void	check_expander_if(t_exp_var exp)
{
	exp.exit_str = ft_itoa(g_last_exit_status);
	exp.var_len = ft_strlen(exp.exit_str);
	if (exp.j + exp.var_len < 8192)
	{
		ft_strncpy(exp.result + exp.j, exp.exit_str, exp.var_len);
		exp.j += exp.var_len;
	}
	free(exp.exit_str);
	exp.i += 2;
}

static void	dc(t_exp_var *exp, char *line)
{
	exp->i++;
	exp->var_start = exp->i;
	while (line[exp->i] && (isalnum(line[exp->i])
			|| line[exp->i] == '_'))
		exp->i++;
}

static void	check_expander_else(t_exp_var *exp, char *line)
{
	exp->var_name = ft_strndup(&line[exp->var_start], exp->i - exp->var_start);
	exp->var_value = getenv(exp->var_name);
	free(exp->var_name);
	if (exp->var_value)
	{
		exp->var_len = ft_strlen(exp->var_value);
		if (exp->j + exp->var_len < 8192)
		{
			ft_strncpy(exp->result + exp->j, exp->var_value, exp->var_len);
			exp->j += exp->var_len;
		}
	}
}

static void	check_exp_while(t_exp_var *exp, char *line, bool *allow_expansion)
{
	while (line[exp->i])
	{
		apic(exp, line);
		if (line[exp->i] == '$' && allow_expansion && exp->status_quote)
		{
			if (line[exp->i + 1] == '?')
			{
				check_expander_if(*exp);
				copy_g_status(exp);
				return ;
			}
			else
			{
				dc(exp, line);
				if (exp->var_start == exp->i)
				{
					exp->result[exp->j++] = '$';
					continue ;
				}
				check_expander_else(exp, line);
			}
		}
		else
			exp->result[exp->j++] = line[exp->i++];
	}
}

char	*expand_variables(char *line, bool global_var_enable,
	bool allow_expansion)
{
	t_exp_var	exp;

	exp.i = 0;
	exp.j = 0;
	exp.status_quote = true;
	exp.result = ft_calloc(8192, sizeof(char *));
	if (!line || !global_var_enable || !exp.result)
	{
		if (line)
			return (ft_strdup(line));
		else
			return (NULL);
	}
	check_exp_while(&exp, line, &allow_expansion);
	exp.result[exp.j] = '\0';
	free(line);
	return (exp.result);
}
