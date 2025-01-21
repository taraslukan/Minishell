#include "read.h"

char *rdLine(char *prompt)
{
	return (readline(prompt));
}

char *build_std_prompt(char *prompt)
{
	char *step;
	step = ft_strjoin("Minishell: ", prompt);
	return (ft_strjoin(step, " ➜> "));
}

char	*start_read(void)
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
