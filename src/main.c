/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:23:13 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/28 21:04:49 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




# include "libft.h"
# include "minishell.h"
#include <stdio.h>
#include <sys/_types/_size_t.h>
#include <sys/fcntl.h>





void leaks()
{
	// size_t p = 0x7fbdb3406580;
	// printf("%s\n",(char *)(p));
    char buffer[256] = {0};
    sprintf(buffer, "/usr/sbin/lsof -p %d",getpid());
    system(buffer);
    system("/usr/bin/leaks minishell");
}


int main(int ac, char **argv, char **env)
{
	// atexit(leaks);

	// int fd = open("log", O_RDWR | O_TRUNC | O_CREAT, 0644);
	// if (fd != 3)
	// 	exit (2);
	(void)ac;
	(void)argv;
	t_env	*envp;
	// if (!isatty(0))
	// 	return (ft_printf(2, "nudejs: require a tty session\n"), 1);
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	envp = env_arr_to_lst(env);
	envp->pwd = set_pwd();
	minishell(envp);
	clean_env(envp);
	rl_clear_history();
	return (0);
}
