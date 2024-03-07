/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:42:11 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/07 14:12:37 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == '\n' || c == '\t' || c == ' '
		|| c == '\v' || c == '\f' || c == '\r');
}

int ft_iskey(char c)
{
	return (c == '|' || c == '<' || c == '>'
			||c == '\0' );
}

int is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int is_sep(char c)
{
	return (ft_iskey(c) || ft_isspace(c));
}
