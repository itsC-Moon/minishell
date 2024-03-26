/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:10:45 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/26 15:22:11 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_status(int status, int opt)
{
	static int _status;
	if (opt == GET)
		return (_status);
	_status = status;
	return (_status);
}


int in_here_doc(int opt)
{
	static int _in_here_doc;

	if (opt == IN)
		_in_here_doc = 1;
	else if (opt  == OUT)
		_in_here_doc = 0;
	return (_in_here_doc);
}
