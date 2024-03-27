

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static void remove_node(t_env	*env, t_lst	*lst)
{
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	if (lst == env->front)
		env->front = lst->next;
	if (lst == env->back)
		env->back = lst->prev;
	free(lst->varible);
	free(lst);
}

int unset_func(t_proc	*proc, t_env	*env, int *fd)
{
	int		i;
	t_lst	*it;
	int		status;

	i = 1;
	status = 0;
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(fd), 1);
	close_fds(proc);
	while (proc->args[i] != NULL)
	{
		it = env_search2(env, proc->args[i]);
		if (it)
			remove_node(env, it);
		i++;
	}
	return (status);
}
