/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:22:57 by fporto            #+#    #+#             */
/*   Updated: 2022/10/30 15:15:54 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Executes "path" executable and returns process PID
pid_t	execute(char *path)
{
	pid_t	pid;
	t_simple_cmd	*currSimpleCmd;

	currSimpleCmd = g_global.fullCmd->currSimpleCmd;
	pid = fork();
	if (pid == -1)
		free_global(CLR_RED"Failed fork"CLR_RST);
	if (!pid)
		if (execve(path, currSimpleCmd->args, g_global.env) == -1)
			free_global(CLR_RED"Failed execve"CLR_RST);
	// else
	// 	wait(NULL);
	return (pid);
}

// Searches individual folder for executable
pid_t	search_dir(t_simple_cmd *sCmd, char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*temp;
	char			*new_path;
	pid_t			ret;
	char			*exec;

	exec = sCmd->args[0];
	ret = 0;
	new_path = ft_strdup(path);
	dir = opendir(path);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!ft_strcmp(entry->d_name, exec))
		{
			new_path = ft_strcat_char(new_path, '/');
			temp = new_path;
			new_path = ft_strjoin(new_path, exec);
			free(temp);
			closedir(dir);
			ret = execute(new_path);
			free(new_path);
			return (ret);
		}
		entry = readdir(dir);
	}
	free(new_path);
	closedir(dir);
	return (ret);
}

// Searches PATH for executable
pid_t	search_path(t_simple_cmd *sCmd)
{
	pid_t	ret;
	int		i;

	ret = 0;
	i = 0;
	while (g_global.path_dirs[i])
	{
		ret = search_dir(sCmd, g_global.path_dirs[i++]);
		if (ret)
			return (ret);
	}
	return (ret);
}

pid_t	not_builtin(t_simple_cmd *sCmd)
{
	return (search_path(sCmd));
	// free_global(NULL);
}
