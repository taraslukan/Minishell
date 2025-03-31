/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:06:23 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/27 13:39:33 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

void	apic(t_exp_var *exp, char *line)
{
	if (line[exp->i] == '\'' && exp->status_quote == true)
		exp->status_quote = false;
	else if (line[exp->i] == '\'' && exp->status_quote == false)
		exp->status_quote = true;
}

void	copy_g_status(t_exp_var *exp)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_itoa(g_last_exit_status);
	while (res[i])
		exp->result[exp->j++] = res[i++];
}

void	free_read(t_exp_var *exp)
{
	if (exp->var_name)
		free(exp->var_name);
	if (exp->var_value)
		free(exp->var_value);
	if (exp->exit_str)
		free(exp->exit_str);
}
