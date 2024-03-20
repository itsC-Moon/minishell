/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:57:48 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/19 02:10:15 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include "libft.h"
// #include "libft.h"
#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libc.h>

int error_func(char *name, int code)
{
	ft_printf(2, "nudejs: %s: %s\n", name, strerror(errno));	
	return (code);
}

int cd_func(t_proc	*proc, t_env	*env)
{
	char path[1024];
	t_lst	*lst;
	char *tmp;
	
	if (open_builtin_files(proc) == 1 || env == NULL)
		return (1);
	if (chdir(proc->args[1]) < 0)
		return (error_func("cd", 1));
	lst = env_search_2(env, "PWD");
	if (lst != NULL)
		free(lst->varible);
	tmp = ft_strdup(getcwd(path, sizeof(path)));
	return (0);
}	

