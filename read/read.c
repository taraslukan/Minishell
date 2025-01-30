#include "read.h"

char *rdLine(char *prompt)
{
	return (readline(prompt));
}

char *build_std_prompt(char *prompt)
{
	char *step;
	char *colored_prompt;

	step = ft_strjoin(BLUE "Minishell: " RESET GREEN, prompt);
	colored_prompt = ft_strjoin(step, RESET YELLOW " ➜ " RESET);
	free(step);
	return (colored_prompt);
}

char *start_read(void)
{
	char *input;
	char cwd[PATH_MAX];
	char *heredocinput;

	getcwd(cwd, sizeof(cwd));
	input = rdLine(build_std_prompt(cwd));
	if (ft_strlen(input) > 0)
	{
		heredocinput = tl_check_heredoc(input);
		if (!heredocinput)
			return (input);
		else
			return (heredocinput);
	}
	return (NULL);
}
