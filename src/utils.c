/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:22:57 by fporto            #+#    #+#             */
/*   Updated: 2022/06/17 18:53:01 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	global_init(char **env)
{
	g_global.exit = 0;
	g_global.env_list = parse_env(env, -1);
	if (!g_global.env_list)
		free_global("Failed env parsing");
}

void	free_arr(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

static void	free_exports(t_export *exports)
{
	t_export	*tmp;

	while (exports)
	{
		tmp = exports->next;
		free(exports->key);
		free(exports->value);
		exports = tmp;
	}
}

void	free_global(char *err)
{
	if (g_global.env_list)
		free_env(g_global.env_list);
	ft_free(g_global.input);
	ft_free(g_global.cwd);
	free_arr(g_global.argv);
	if (g_global.exports)
		free_exports(g_global.exports);
	ft_free(g_global.exports);
	rl_clear_history();
	if (err)
	{
		printf("Error: %s\n", err);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
