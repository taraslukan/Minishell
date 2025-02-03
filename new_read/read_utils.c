/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:05:03 by fluzi             #+#    #+#             */
/*   Updated: 2025/02/03 15:31:48 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

char *build_std_prompt()
{
	char	*step;
	char	*colored_prompt;
	char	prompt[PATH_MAX];

	getcwd(prompt, sizeof(prompt));
	step = ft_strjoin(YELLOW "✗ " BLUE "Minishell: " RESET GREEN, prompt);
	colored_prompt = ft_strjoin(step, RESET YELLOW " ➜ " RESET);
	free(step);
	return (colored_prompt);
}
