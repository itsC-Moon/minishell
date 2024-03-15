/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:41:41 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/15 13:28:32 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	(void)env;

	t_env	*envp = env_arr_to_lst(env);
	const char *buffer = "cat -pwd| <hi >>hello -ls | ls >file1 <file2 >>file3 <file4 >>file5";
	t_mini mini = parser(buffer, envp);
	print_mini(mini);

	// it = mini.proc[1];
	// print2d(it.args, it.nb_args);
	// print_file(it.file, it.nb_file);
	// it = mini.proc[2];
	// print2d(it.args, it.nb_args);
	// print_file(it.file, it.nb_file);
	// // print_mini(mini);


	return EXIT_SUCCESS;
}
