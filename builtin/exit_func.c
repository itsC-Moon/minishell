/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:29:28 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/16 19:22:26 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != 0)
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

static int	is_long(char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	result = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != 0)
	{
		result = result * 10 + (str[i] - 48);
		if (result > 9223372036854775807 && sign == 1)
			return (0);
		else if ((result) > 9223372036854775808UL && sign == -1)
			return (0);
		i++;
	}
	return (1);
}

static int	check_arg(char *arg)
{
	if (arg[0] == 0)
		return (ft_printf(2,
				"nudejs: exit: %s: numeric argument required\n", arg), -1);
	if (is_numeric(arg) == 0)
		return (ft_printf(2,
				"nudejs: exit: %s: numeric argument required\n", arg), -1);
	if (is_long(arg) == 0)
		return (ft_printf(2,
				"nudejs: exit: %s: numeric argument required\n", arg), -1);
	return (0);
}

int	exit_func(t_proc	*proc, int *tmp)
{
	close_builtin_file(tmp);
	if (open_builtin_files(proc) == 1)
		return (1);
	close_fds(proc);
	if (proc->nb_args > 2)
	{
		ft_printf(2, "nudejs: exit: too many arguments\n");
		return (1);
	}
	if (proc->args[1] != NULL && check_arg(proc->args[1]) == -1)
		exit (2);
	if (proc->nb_args == 2 && (proc->args[1] != NULL) && proc->args[1][0] != 0)
		exit(ft_atoi(proc->args[1]));
	else
		exit(0);
	return (0);
}
