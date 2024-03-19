/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:09:03 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/19 11:09:09 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>

int main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	(void)env;

	t_env	*envp = env_arr_to_lst(env);
	// char *path = env_search(envp, "PATH");
	char *buffer;
	while ((buffer = readline("nudejs>$ ")) != NULL)
	{
		t_mini mini = parser(buffer, envp);
		print_mini(mini);
	}

	// char *buffer = "pwd <'$PWD' |  << hello' world' << EOF";
	// t_mini mini = parser(buffer, envp);
	// print_mini(mini);
	// mini.proc[3];
	return (0);
}
