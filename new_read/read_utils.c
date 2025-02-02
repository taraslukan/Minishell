/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluzi <fluzi@student.42roma.it>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:05:03 by fluzi             #+#    #+#             */
/*   Updated: 2025/01/31 18:11:28 by fluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"


bool is_history(char *line)
{
    HIST_ENTRY **history;
    bool ret = false;
    int i = 0;

    history = history_list();
    if (history)
    {
        while (history[i]) {
            if (strcmp(line, history[i]->line) == 0)
            {
                printf("find\n");
                ret = true;
                break;
            }
            i++;
        }
    }
    printf("fatto\n");
    return ret;
}


char *build_std_prompt()
{
    char    *step;
    char    *colored_prompt;
    char    prompt[PATH_MAX];
    
    getcwd(prompt, sizeof(prompt));
    step = ft_strjoin(YELLOW "✗ " BLUE "Minishell: " RESET GREEN, prompt);
    colored_prompt = ft_strjoin(step, RESET YELLOW " ➜ " RESET);
    free(step);
    return (colored_prompt);
}
