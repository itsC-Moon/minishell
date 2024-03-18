/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:57:48 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/18 21:43:24 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include "libft.h"
#include <unistd.h>
#include <libc.h>
int cd_func()

int main(int argc, char **argv, char **envp)
{
	if (argv[0] == NULL || argc < 1)
		return (-1);
	char **ls = malloc(2);
	ls[0] = "ls";
	ls[1] = NULL;
	chdir("../include/");
	execve("/bin/ls", ls, envp);
}
