/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/04/24 05:16:52 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t->env_name = ft_calloc(name, 1);
	if (!t->env_name)
		return (NULL);
	t->env_value = ft_calloc(value, 1);
	if (!t->env_value)
		free(t->env_name);
	if (!t->env_value)
		return (NULL);
	ft_strlcpy(t->env_name, env, name);
	ft_strlcpy(t->env_value, &env[name], value);
	return (t);
}

int	parseenv(char **env, t_env **env_vars, int a)
{
	t_env *e;

	e = NULL;
	while (env[++a])
	{
		if (!e)
		{
			e = new_env(env[a]);
			if (!e)
				return (0);
			*env_vars = e;
		}
		else
		{
			e->next = new_env(env[a]);
			if (!e->next)
				return (0);
			e = e->next;
		}
	}
	return (1);
}

void	freenv(t_env *env_vars)
{
	t_env *tmp;

	while (env_vars)
	{
		if (env_vars->env_name)
			free(env_vars->env_name);
		if (env_vars->env_value)
			free(env_vars->env_value);
		tmp = env_vars->next;
		free(env_vars);
		env_vars = tmp;
	}
}

void	read_command()
{
	char	*input;
	char	**argv;
	int		i;

	input = readline("Gui:x5>");
	argv = split_args(input);

	i = -1;
	while (argv[++i])
		printf("argv[%d]: %s\n", i, argv[i]);


	free(input);
	i = -1;
	while (argv[++i])
		free(argv[i]);
	
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**params;
	t_env	*env_vars;

	// for (int i = 0; env[i]; i++)
	// 	printf("%s\n", env[i]);
	if (!parseenv(env, &env_vars, -1))
	{
		freenv(env_vars); //free if erro malloc
		free(env_vars);
		return (0);
	}
	// while (1)
	// {
	// 	// show_prompt();
	// 	// read_command(input, params);
	// }


	return (0);
}
