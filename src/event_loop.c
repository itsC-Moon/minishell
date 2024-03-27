




#include "minishell.h"

void minishell(t_env *envp)
{
	t_mini	mini;
	char	*buffer;
	int		status = 0;

	while (1)
	{
		buffer = readline("nudejs>$ ");
		if (!buffer)
			return ;
		if (is_empty(buffer))
		{
			free(buffer);
			continue;
		}
		// add_history(buffer);
		mini = parser(buffer, envp);
		free(buffer);
		if (mini.size == 0 && mini.nb_doc == 0)
			continue;
		mini.status = status;
		init_procs(&mini);
		status = mini.status;
		get_status(status, SET);
		clean_mini(&mini);
	}
}
