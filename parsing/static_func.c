/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:10:45 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/22 22:13:29 by hibenouk         ###   ########.fr       */
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
