/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:15:16 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/21 22:33:33 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void error(const char *name)
{
	ft_printf(2, "nudejs: %s: %s\n", name, strerror(errno));	
}

void error_exit(const char *name, int code)
{
	ft_printf(2, "nudejs: %s: %s\n", name, strerror(errno));	
	exit(code);
}

void report(const char *name)
{
	ft_printf(2, "nudejs: %s\n", name);	
}

void check_null(void *ptr, const char *str)
{
	ft_printf(3, "%p =>%s\n",ptr,str);
	if (ptr)
		return ;
	ft_printf(2, "nudejs: %s: %s\n", str, strerror(errno));	
	exit(1);
}
