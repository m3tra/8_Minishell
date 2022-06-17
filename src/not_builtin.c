/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:22:57 by fporto            #+#    #+#             */
/*   Updated: 2022/06/17 18:50:46 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_exists(char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp;
	int				ret;

	ret = 0;
	tmp = ".";
	dir = opendir(tmp);
	if (dir)
	{
		entry = readdir(dir);
		while (entry != NULL)
		{
			if (!ft_strcmp(entry->d_name, cmd))
				ret = 1;
			// printf("%s\n", entry->d_name);
			entry = readdir(dir);
		}
		closedir(dir);
	}
	return (ret);
}

void	not_builtin(void)
{
	char	*path;

	if (command_exists(g_global.argv[0]))
	{
		path = ft_strjoin(g_global.cwd, g_global.argv[0]);
		// printf("path: %s\n", path);
		// printf("argv:\n");
		// for (size_t i = 0; g_global.argv[i]; i++)
		// 	printf("  %s\n", g_global.argv[i]);
		// printf("envp:\n");
		// for (size_t i = 0; g_global.envp[i]; i++)
		// 	printf("  %s\n", g_global.envp[i]);
		execve(path, g_global.argv, g_global.envp);
		free(path);
	}
	free_global(NULL);
}
