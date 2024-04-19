/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:30:19 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/19 11:23:04 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static char	**get_paths(t_env	*env)
{
	char	*path;
	char	**paths;

	path = env_search(env, "PATH");
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (*paths == NULL)
		return (NULL);
	return (paths);
}

static int	get_path_loupe(char ***paths, char **tmp_cmd,
		char **tmp_path, char **path)
{
	int	i;

	i = 0;
	while (access(*path, F_OK | X_OK) == -1)
	{
		if (access(*path, F_OK) == 0)
		{
			free(*tmp_path);
			*tmp_path = *path;
		}
		else
			free(*path);
		if ((*paths)[i] == NULL)
			break ;
		*path = ft_strjoin((*paths)[i], *tmp_cmd);
		i++;
	}
	return (i);
}

static char	*get_path(char **paths, char *cmd)
{
	char	*tmp_cmd;
	char	*path;
	char	*tmp_path;
	int		i;

	tmp_path = NULL;
	path = ft_strdup("");
	tmp_cmd = ft_strjoin("/", cmd);
	i = get_path_loupe(&paths, &tmp_cmd, &tmp_path, &path);
	if (paths[i] == NULL && tmp_path != NULL)
		return (free(tmp_cmd), tmp_path);
	else if (paths[i] == NULL)
		return (free(tmp_cmd), cmd);
	return (free(tmp_cmd), free(tmp_path), path);
}

static char	*null_path_handle(t_proc *proc)
{
	char	*pwd;
	char	*cmd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return ("");
	cmd = ft_strjoin("/", proc->args[0]);
	tmp = ft_strjoin(pwd, cmd);
	return (free(cmd), free(pwd), tmp);
}

char	*get_cmd_path(t_proc	*proc, t_env *env)
{
	char	**paths;
	char	*cmd;

	paths = get_paths(env);
	if (proc->args[0][0] == 0 || ft_strchr(proc->args[0], '/') != NULL)
		return (free_tab(paths), ft_strdup(proc->args[0]));
	if (paths == NULL || paths[0][0] == 0)
		return (free_tab(paths), null_path_handle(proc));
	cmd = get_path(paths, proc->args[0]);
	return (free_tab(paths), cmd);
}
