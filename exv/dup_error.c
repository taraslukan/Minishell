/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:29:54 by fluzi             #+#    #+#             */
/*   Updated: 2025/03/04 17:35:14 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exv.h"

void	error_dup_input(void)
{
	perror("Error opening input file");
	exit(EXIT_FAILURE);
}

void	error_dup_output(void)
{
	perror("Error opening output file");
	exit(EXIT_FAILURE);
}

void	dup_close(int out_fd)
{
	perror("Error duplicating stdout");
	if (out_fd >= 0)
		close(out_fd);
	exit(EXIT_FAILURE);
}
