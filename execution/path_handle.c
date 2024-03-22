/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:44:58 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/21 21:17:40 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "minishell.h"

char **get_paths(t_env	*env)
{
	char *path;
	char **paths;

	path = env_search(env, "PATH");
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (*paths == NULL)
		return (NULL);
	return (paths);
}

char *get_path(char **paths, char *cmd)
{
	char *tmp_cmd;
	char *path;
	char *tmp_path;
	int i;

	i = 0;
	tmp_path = NULL;
	path = NULL;
	tmp_cmd = ft_strjoin("/", cmd);
	while (access(path, F_OK | X_OK) == -1)
	{
		if (access(path, F_OK) == 0)
		{
			free(tmp_path);
			tmp_path = path;
		}
		else
			free(path);
		if (paths[i] == NULL)
			break;
		path =  ft_strjoin(paths[i], tmp_cmd);
		i++;
	}
	if (paths[i] == NULL && tmp_path != NULL)
		return (free(tmp_cmd), tmp_path);
	else if (paths[i] == NULL)
		return (free(tmp_cmd), cmd);
	return (free(tmp_cmd), free(tmp_path), path);
}

char *get_cmd_path(t_proc	*proc, t_env *env)
{
	char **paths;
	char *cmd;

	paths = get_paths(env);
	if (proc->args[0][0] == 0 || ft_strchr(proc->args[0], '/') != NULL || paths == NULL)
		return (free_tab(paths), ft_strdup(proc->args[0])); // TODO : free paths;
	cmd = get_path(paths, proc->args[0]);
	return (free_tab(paths), cmd); // TODO : free paths;
}
// int main(int argc, char **argv, char **envp)
// {
// 	t_env *env = env_arr_to_lst(envp);
// 	t_proc proc;

// 	proc.args = &argv[1];
// 	proc.command = get_cmd_path(&proc, env);
// 	if (argc < 1 || argv[0] == NULL)
// 		return (1);
// 	printf("cmd path == %s\n", proc.command);
// 	check_cmd(&proc, proc.command);

// 	return (EXIT_SUCCESS);
// }
