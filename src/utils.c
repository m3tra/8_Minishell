/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:22:57 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 07:25:11 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	global_init(char **env)
{
	g_global.env = parse_env(env, -1);
	if (!g_global.env)
		free_global();
}

static void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->content);
		list = tmp;
	}
}

void	free_global(void)
{
	int a;

	if (g_global.env)
		free_env(g_global.env);
	if (g_global.input)
		free(g_global.input);
	if (g_global.cwd)
		free(g_global.cwd);
	if (g_global.argv)
	{
		a = -1;
		while (g_global.argv[++a])
			free(g_global.argv[a]);
		free(g_global.argv);
	}
	if (g_global.exports)
		free_list(g_global.exports);
	if (g_global.exports)
		free(g_global.exports);
	exit(EXIT_SUCCESS);
}
