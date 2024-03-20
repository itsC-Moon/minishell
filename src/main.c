/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:06:25 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 20:23:03 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>


int main(int ac, char **argv, char **env)
{
    // atexit(leak);
    t_mini mini;
    (void)ac;
    (void)argv;
    (void)env;


	ft_printf(2, "child %d\n",getpid());
    t_env    *envp = env_arr_to_lst(env);
    char *buffer;
    while ((buffer = readline("nudejs>$ ")) != NULL)
    {
        mini = parser(buffer, envp);
		// printf("--->%s", mini.proc[0].args[0]);
        mini.envp = envp;
        init_procs(&mini);
		buffer = NULL;
    }
	ft_printf(2, "child %d\n",getpid());
	// ft_printf(2, "child %d",getpid());
	perror("check");
	// perror("check");
    // print_mini(mini)m
    // init_procs(&mini);    
    // it = mini.proc[1];
    // print2d(it.args, it.nb_args);
    // print_file(it.file, it.nb_file);
    // it = mini.proc[2];
    // print2d(it.args, it.nb_args);
    // print_file(it.file, it.nb_file);
    // // print_mini(mini);

    // exit(mini.status);
}
