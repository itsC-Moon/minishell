/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 00:59:14 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/22 13:29:23 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TMP_H
# define TMP_H

# include "../include/minishell.h"
char *env_search(t_env	*env, const char *name);
char	**ft_split(char *s, char c);
t_env	*env_arr_to_lst(char **envp);
char **env_lst_to_arr(t_env *env);
char	*ft_strchr(const char	*s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	check_cmd(t_proc	*proc, char *cmd);
int		ft_strcmp(const char *s1, const char *s2);
void	open_files(t_proc	*proc);
void get_io_files(t_proc	*proc);
char *get_cmd_path(t_proc	*proc, t_env *env);
#endif
