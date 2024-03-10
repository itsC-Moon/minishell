/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:02:37 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/10 10:45:12 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
void get_type(t_Token_Type type) {
  switch (type) {
    case STRING_LTR:
      printf("STRING_LTR\n");
      break;
    case PIPE:
      printf("PIPE\n");
      break;
    case INPUT_REDIR:
      printf("INPUT_REDIR\n");
      break;
    case OUTPUT_REDIR:
      printf("OUTPUT_REDIR\n");
      break;
    case APPEND_REDIR:
      printf("APPEND_REDIR\n");
      break;
    case HEREDOC:
      printf("HEREDOC\n");
      break;
  };
}
