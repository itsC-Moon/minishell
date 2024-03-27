/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:23:13 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/27 23:35:36 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




# include "libft.h"
# include "minishell.h"
#include <stdio.h>
#include <sys/_types/_size_t.h>
#include <sys/fcntl.h>


int event(void) {return 0;}
void    ft_signal_ctrl_c(int sig)
{
    (void)sig;
    write(2, "\n", 1);
	// rl_done = 1337;
	// rl_event_hook = event;
	// rl_replace_line("", 0);
 //    rl_on_new_line();
 //    rl_redisplay();
}

void ft_ignore(int sig)
{
	(void)sig;
    // rl_on_new_line();
}

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
	atexit(leaks);

	int fd = open("log", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd != 3)
		exit (2);
	(void)ac;
	(void)argv;
	t_env	*envp;
	// if (!isatty(0))
	// 	return (ft_printf(2, "nudejs: require a tty session\n"), 1);
	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, ft_ignore);
	envp = env_arr_to_lst(env);
	envp->pwd = set_pwd();
	minishell(envp);
	clean_env(envp);
	// rl_clear_history();
	return (0);
}
