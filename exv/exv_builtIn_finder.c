/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exv_builtIn_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:23:24 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/20 16:59:41 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

static char	**built_in_finder(void)
{
	static char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};

	return (builtins);
}

bool	is_builtin(const char *cmd)
{
	int		i;
	char	**builtins;

	i = 0;
	builtins = built_in_finder();
	while (builtins[i])
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
