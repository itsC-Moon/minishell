




#include "minishell.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

static void execute(t_mini *mini)
{
	signal(SIGQUIT, signal_ignore);
	init_procs(mini);
	signal(SIGQUIT, SIG_IGN);
	get_status(mini->status, SET);
	clean_mini(mini);
}

void minishell(t_env *envp)
{
	char			*buffer;
	t_mini			mini;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		check_exit(NORM, SET);
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
		if (mini.size == 0 && mini.nb_doc == 0)
			continue;
		execute(&mini);
		get_status(mini.status, SET);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}
