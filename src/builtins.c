/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:02:20 by fporto            #+#    #+#             */
/*   Updated: 2022/11/27 22:41:47 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env"));
}

int	builtin(t_simple_cmd *sCmd)
{
	t_env	*tmp;
	char	*cmd;

	cmd = sCmd->args[0];
	if (!is_builtin(cmd))
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		echo(sCmd);
	else if (!ft_strcmp(cmd, "pwd"))
		printf("%s\n", g_global.cwd);
	// else if (!ft_strcmp(cmd, "cd"))
		// cd();
	else if (!ft_strcmp(cmd, "export"))
		export();
	else if (!ft_strcmp(cmd, "unset"))
		unset(g_global.argv[1]);
	else if (!ft_strcmp(cmd, "env"))
	{
		tmp = g_global.env_list;
		while (tmp)
		{
			printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	// else if (!ft_strcmp(cmd, "exit"))
		// free_global(NULL);
	// free_global(NULL);
	return (1);
}
