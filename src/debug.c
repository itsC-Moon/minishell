/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:02:37 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/08 16:06:31 by hibenouk         ###   ########.fr       */
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
    case INPUT_REDIRECT:
      printf("INPUT_REDIRECT\n");
      break;
    case OUTPUT_REDIRECT:
      printf("OUTPUT_REDIRECT\n");
      break;
    case APPEND_REDIRECT:
      printf("APPEND_REDIRECT\n");
      break;
    case HEREDOC:
      printf("HEREDOC\n");
      break;
  };
}
