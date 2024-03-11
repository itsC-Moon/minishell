/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2d2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:32:40 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/11 01:31:03 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "test.h" // ft_strdup prototype 

t_lst *lst_addback(t_lst	*lst, char *to_add)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_lst));
	tmp->next->next = NULL;
	tmp->next->prev = tmp;
	tmp->next->varible = to_add;
	return (tmp->next);
}

t_env	*env_arr_to_lst(char **envp)
{
	t_env	*env;
	t_lst	*lst;
	int		i;
	t_lst	*tmp;

	i = 0;
	lst = malloc(sizeof(t_lst));
	if (lst == NULL)
		exit(1);
	env = malloc(sizeof(t_env));
	if (env == NULL)
		exit(1);
	lst->varible = envp[i++];
	lst->next = NULL;
	lst->prev = NULL;
	while (envp[i] != NULL)
		tmp = lst_addback(lst, envp[i++]);
	env->back = tmp;
	env->front = lst;
	env->size = i;
	return (env);
}

char **env_lst_to_arr(t_env *env)
{
	t_lst *lst = env->front;
	char **arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(char *) * (env->size + 1));
	if (arr == NULL)
		exit (1);
	while (lst != NULL)
	{
		arr[i] = ft_strdup(lst->varible);
		lst = lst->next;
		i++;
	}

	arr[i] = NULL;
	return (arr);
}

// int main(int argc, char **argv, char **envp)
// {
// 	if (argc < 1 && argv[0] == NULL)
// 		return (0);
// 	t_env *env = env_arr_to_lst(envp);
// 	printf("front --> %s\n", env->front->varible);
// 	printf("back --> %s\n", env->back->varible);
// 	printf("front --> %ld\n", env->size);
// 	t_lst *lst = env->front;
// 	int i = 0;
// 	while (lst != NULL)
// 	{
// 		// printf("var%d=%s\n", (i + 1), lst->varible);
// 		lst = lst->next;
// 		i++;
// 	}
// 	char **envs = env_lst_to_arr(env);
// 	i = 0;
// 	printf("-----------------------------arr_to_lst----------------------------------\n");
// 	while (envs[i] != NULL)
// 	{
// 		printf("var %d --> %s\n", i + 1, envs[i]);
// 		i++;
// 	}
// }

