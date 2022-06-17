/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:02:20 by fporto            #+#    #+#             */
/*   Updated: 2022/06/17 18:48:52 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env"));
}

void	builtin(void)
{
	t_env	*tmp;

	if (!is_builtin(g_global.argv[0]))
		return ;
	if (!ft_strcmp(g_global.argv[0], "echo"))
		echo();
	else if (!ft_strcmp(g_global.argv[0], "pwd"))
		printf("%s\n", g_global.cwd);
	// else if (!ft_strcmp(g_global.argv[0], "cd"))
		// cd();
	else if (!ft_strcmp(g_global.argv[0], "export"))
		export();
	else if (!ft_strcmp(g_global.argv[0], "unset"))
		unset(g_global.argv[1]);
	else if (!ft_strcmp(g_global.argv[0], "env"))
	{
		tmp = g_global.env_list;
		while (tmp)
		{
			printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	// else if (!ft_strcmp(g_global.argv[0], "exit"))
		// free_global(NULL);
	free_global(NULL);
}
