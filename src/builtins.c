/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:02:20 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 01:36:39 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_dir_in_path(char *path)
{
	char	*temp;
	int	i;

	i = 0;
	while (path[i] && path[i] != '/')
		i++;
	if (!i)
		return (NULL);
	temp = malloc(sizeof(char) * i + 1);
	if (!temp)
		exit(EXIT_FAILURE);
	i = 0;
	while (path[i] && path[i] != '/')
		temp[i] = path[i];
	temp[i] = '\0';
	return (temp);
}

void	up_path(char *path)
{
	int	count;
	int	i;
	char	*tmp;

	count = 0;
	i = 0;
	while (path[i])
	{
		tmp = get_next_dir_in_path(path);
		if (!ft_strcmp(tmp, ".."))
			count++;
	}
}

char	*args_only(void)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (g_global.input[i] && g_global.input[i] != ' ')
		i++;
	ret = ft_strdup(g_global.input + i + 1);
	if (!ret)
		exit(EXIT_FAILURE);
	return (ret);
}

void	print_exports(void)
{
	t_list		*list;
	t_export	*export;

	list = g_global.exports;
	printf("Exports:\n");
	while (list)
	{
		export = (t_export *)list->content;
		printf("%s=%s\n", export->key, export->value);
		list = list->next;
	}
}

void	add_to_exported()
{
	char	*arg;
	t_export	*export;
	int	key_len;
	int	value_len;
	int	i;

	arg = g_global.argv[1];
	export = malloc(sizeof(t_export));
	if (!export)
		exit(EXIT_FAILURE);
	key_len = 0;
	while(arg[key_len] && arg[key_len] != '=')
		key_len++;
	export->key = malloc(sizeof(char) * key_len + 1);
	i = -1;
	while (++i < key_len)
		export->key[i] = arg[i];
	export->key[i] = '\0';
	value_len = 0;
	while(arg[key_len + value_len + 1])
		value_len++;
	export->value = malloc(sizeof(char) * value_len + 1);
	i = -1;
	while (arg[key_len + ++i + 1])
		export->value[i] = arg[key_len + i + 1];
	export->value[value_len] = '\0';
	if (!g_global.exports)
		g_global.exports = ft_lstnew((void *)export);
	else
		ft_lstadd_back(&g_global.exports, ft_lstnew((void *)export));
	print_exports();
}

void	rm_from_exported(char *var)
{
	t_list	*iter;
	t_list	*tmp;
	t_export	*cont;
	t_export	*rm;

	iter = g_global.exports;
	if (iter->next)
		cont = (t_export *)iter->next->content;
	while (iter->next && ft_strcmp(cont->key, var))
	{
		cont = (t_export *)iter->next->content;
		iter = iter->next;
	}
	tmp = iter->next;
	rm = (t_export *)tmp->content;
	if (iter->next->next)
		iter->next = iter->next->next;
	else
		iter->next = NULL;
	free (rm->key);
	free (rm->value);
	print_exports();
}

void	builtin(char **argv)
{
	// char	*temp;
	// char	*pwd;
	char	*echo;
	t_env	*tmp;

	if (!ft_strcmp(argv[0], "echo"))
	{
		echo = args_only();
		printf("%s\n", echo);
		free(echo);
	}
	else if (!ft_strcmp(argv[0], "pwd"))
	{
		if (!g_global.cwd)
			printf("Failed to execute command \"%s\"\n", argv[0]);
		else
			printf("%s\n", g_global.cwd);
		// free(pwd);
	}
	else if (!ft_strcmp(argv[0], "cd"))
	{
		if (chdir(argv[1]) == -1)
		{
			if (errno == ENOENT)
				printf("cd: no such file or directory: %s", argv[1]);
			printf("Failed to execute command \"%s\"\n", argv[0]);
		}
	}
	else if (!ft_strcmp(argv[0], "export"))
		add_to_exported();
	else if (!ft_strcmp(argv[0], "unset"))
		rm_from_exported(argv[1]);
	else if (!ft_strcmp(argv[0], "env"))
	{
		tmp = g_global.env;
		while (g_global.env)
		{
			printf("%s=%s\n", g_global.env->name, g_global.env->value);
			g_global.env = g_global.env->next;
		}
		g_global.env = tmp;
	}
	else if (!ft_strcmp(argv[0], "exit"))
		exit(EXIT_SUCCESS);
}
