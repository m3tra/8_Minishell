/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 05:07:47 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global g_global;

int	global_init(char **env)
{
	g_global.env = parseenv(env, -1);
	if (!g_global.env)
		return (0);
	return (1);
}

int	ft_strlenchar(const char *str, char character)
{
	int	a;

	a = 0;
	while (str[a] != '\0' && str[a] != character)
		a++;
	return (a);
}

t_env *new_env(char *env)
{
	t_env *t;
	int name;
	int value;

	t = ft_calloc(1, sizeof(t_env));
	if (!t)
		return (NULL);
	name = ft_strlenchar(env, '=') + 1;
	value = ft_strlen(&env[name]) + 1;
	t->name = ft_calloc(name, 1);
	if (!t->name)
		return (NULL);
	t->value = ft_calloc(value, 1);
	if (!t->value)
		free(t->name);
	if (!t->value)
		return (NULL);
	ft_strlcpy(t->name, env, name);
	ft_strlcpy(t->value, &env[name], value);
	return (t);
}

t_env	*parseenv(char **env, int a)
{
	t_env *e;
	t_env *tmp;

	e = NULL;
	while (env[++a])
	{
		if (!e)
		{
			e = new_env(env[a]);
			if (!e)
				return (0);
			tmp = e;
		}
		else
		{
			e->next = new_env(env[a]);
			if (!e->next)
				return (0);
			e = e->next;
		}
	}
	return (tmp);
}

void	freenv(t_env *env_vars)
{
	t_env *tmp;

	while (env_vars)
	{
		if (env_vars->name)
			free(env_vars->name);
		if (env_vars->value)
			free(env_vars->value);
		tmp = env_vars->next;
		free(env_vars);
		env_vars = tmp;
	}
}

void	freelist(t_list	*list)
{
	t_list *tmp;
	while(list)
	{
		tmp = list->next;
		free(list->content);
		list = tmp;
	}
}

void	free_global()
{
	int a;

	if (g_global.env)
		freenv(g_global.env);
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
		freelist(g_global.exports);
	if (g_global.exports)
		free(g_global.exports);
	exit(EXIT_SUCCESS);
}

char	*last_dir()
{
	size_t	len;
	int	i;

	i = 0;
	len = ft_strlen(g_global.cwd);
	while (len > 0 && g_global.cwd[len - 1] != '/')
		len--;
	return (ft_strdup(g_global.cwd + len));
}

void	read_command()
{
	// char	*input;
	// char	**argv;
	// int		i;
	char	*tmp;
	char	*prompt;
	char	*last;

	g_global.cwd = getcwd(NULL, INPUT_LEN);
	prompt = ft_strdup(PROMPT);
	last = last_dir();
	tmp = ft_strjoin(last, prompt);
	free(last);
	free(prompt);
	g_global.input = readline(tmp);
	while (!g_global.input)
		readline(tmp);

	g_global.argv = split_args(g_global.input);

	// i = -1;
	// while (g_global.argv[++i])
	// 	printf("argv[%d]: %s\n", i, g_global.argv[i]);


	builtin(g_global.argv);
	// free(input);
	// i = -1;
	// while (argv[++i])
	// 	free(argv[i]);
	free(tmp);
	// exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	// pid_t	id;
	// t_env	*env_vars;
	// char	*input;
	// char	**params;
	// char	*cmd;
	(void)env;
	(void)argc;
	(void)argv;
	// for (int i = 0; env[i]; i++)
	// 	printf("%s\n", env[i]);


	if (!global_init(env))
		free_global();
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, );
	while (1)
	{
		// if (!ft_strcmp(argv[0], "cd"))
		// 	chdir(argv[1]);
		// id = fork();
		// if (id)
		// 	wait(NULL);
		// else
		// {
		read_command();
		// }
	}
	free_global();
}
