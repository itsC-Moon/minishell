/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:23:13 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/04 21:57:12 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




# include "libft.h"
# include "minishell.h"

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
	t_env	*envp;

	(void)ac;
	(void)argv;
	if (!isatty(0))
		return (ft_printf(2, "nudejs: require a tty session\n"), 1);
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	envp = env_arr_to_lst(env);
	envp->pwd = set_pwd();
	minishell(envp);
	clean_env(envp);
	rl_clear_history();
	return (get_status(0, GET));
}
