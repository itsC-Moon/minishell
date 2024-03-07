/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:18:31 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/07 16:06:46 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int get_len(const char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] && !ft_iskey(buffer[i]))
	{
		if (is_quote(buffer[i]))
			i += quote_s(buffer+ i, SKIP, NULL);
		else
			i++;
	}
	return (i);
}


int	get_args(const char *buffer, t_Token *tokens)
{
	int		i;
	int		len;
	char	*args;
	t_list	*list;
	
	len =get_len(buffer);
	args = malloc(sizeof(char) * len + 1);
	check_null(args, "malloc");
	i = -1;
	while (++i < len)
		args[i] = buffer[i];
	args[i] = '\0';
	list = lst(args, STRING_LTR);
	check_null(list, "malloc");
	addback(tokens, list);
	return (len);
}


