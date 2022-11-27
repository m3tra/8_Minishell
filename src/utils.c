/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:22:57 by fporto            #+#    #+#             */
/*   Updated: 2022/11/27 11:37:27 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cwd(void)
{
	ft_free(g_global.cwd);
	g_global.cwd = getcwd(NULL, INPUT_LEN);
	if (!g_global.cwd)
		free_global(CLR_RED"Failed getting CWD"CLR_RST);
}

void	global_init(char **env)
{
	// t_full_cmd	*t_cmd;

	g_global.env = env;

	// printf("env:\n");
	// print_str_array(env);

	g_global.exit = 0;
	// printf("1cwd ptr: %p\ncwd cnt: %s\n", &g_global.cwd, g_global.cwd);
	g_global.env_list = parse_env(env, -1);
	if (!g_global.env_list)
		free_global(CLR_RED"Failed env parsing"CLR_RST);
	update_cwd();

	// t_cmd = malloc(sizeof(t_full_cmd));
	// if (!t_cmd)
	// 	free_global(CLR_RED"Failed malloc of t_cmd"CLR_RST);

	parse_path();
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

void	free_full_cmd(void)
{
	int	i;

	i = 0;
	if (!g_global.full_cmd)
		return ;
	while (i < g_global.full_cmd->n_simple_cmds)
		ft_free(g_global.full_cmd->simple_cmds[i++]);
	ft_free(g_global.full_cmd);
}

void	free_global(char *err)
{
	if (g_global.env_list)
		free_env(g_global.env_list);
	ft_free(g_global.input);
	ft_free(g_global.cwd);
	free_arr(g_global.argv);
	free_full_cmd();
	if (g_global.exports)
		free_exports(g_global.exports);
	ft_free(g_global.exports);
	rl_clear_history();
	if (err)
		perror(err);
	exit(EXIT_SUCCESS);
}
