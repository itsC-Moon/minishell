




#include "minishell.h"
#include <termios.h>
#include <unistd.h>

void minishell(t_env *envp)
{
	t_mini	mini;
	char	*buffer;
	int		status = 0;
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		check_exit(NORM);
		buffer = readline("nudejs>$ ");
		if (!buffer)
			return ;
		if (is_empty(buffer))
		{
			free(buffer);
			continue;
		}
		add_history(buffer);
		mini = parser(buffer, envp);
		free(buffer);
		if (mini.size == 0 && mini.nb_doc == 0)
			continue;
		mini.status = status;
		signal(SIGQUIT, signal_ignore);
		init_procs(&mini);
		signal(SIGQUIT, SIG_IGN);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		status = mini.status;
		get_status(status, SET);
		clean_mini(&mini);
	}
}
