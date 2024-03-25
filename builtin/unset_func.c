

#include "minishell.h"
#include "libft.h"

static void remove_node(t_env	*env, t_lst	*lst)
{
	free(lst->varible);
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	if (lst == env->front)
		env->front = lst->next;
	if (lst == env->back)
		env->back = lst->prev;
	free(lst);
}

int unset_func(t_proc	*proc, t_env	*env, int *fd)
{
	int i;
	char *tmp;
	int status;

	i = 1;
	status = 0;
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(fd), 1);
	close_fds(proc);
	while (proc->args[i] != NULL)
	{
		tmp = env_search_3(env, proc->args[i]);
		if (tmp == NULL)
			i++;
		else if (ft_strcmp(tmp, "$") == 0)
		{
			ft_printf(2, "nudejs: unset: %s: not a valid identifier\n", proc->args[i++]);
			status = 1;
		}
		else
		{
			remove_node(env, env_search_2(env, proc->args[i++]));
			env->size--;
		}
	}
	return (status);
}
