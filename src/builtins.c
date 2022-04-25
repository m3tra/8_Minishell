/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:02:20 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 07:34:38 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(char **argv)
{
	t_env	*tmp;

	if (!ft_strcmp(argv[0], "echo"))
		echo();
	else if (!ft_strcmp(argv[0], "pwd"))
		printf("%s\n", g_global.cwd);
	else if (!ft_strcmp(argv[0], "cd"))
		cd();
	else if (!ft_strcmp(argv[0], "export"))
		export();
	else if (!ft_strcmp(argv[0], "unset"))
		unset(argv[1]);
	else if (!ft_strcmp(argv[0], "env"))
	{
		tmp = g_global.env;
		while (tmp)
		{
			printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	else if (!ft_strcmp(argv[0], "exit"))
		free_global();
}
