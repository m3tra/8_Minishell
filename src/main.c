/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/04/24 03:01:23 by fheaton-         ###   ########.fr       */
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
	t->env_n = ft_calloc(name, 1);
	if (!t->env_n)
		return (NULL);
	t->env_v = ft_calloc(value, 1); 
	if (!t->env_v)
		free(t->env_n);
	if (!t->env_v)
		return (NULL);
	ft_strlcpy(t->env_n, env, name);
	ft_strlcpy(t->env_v, &env[name], value);
	return (t);
}

int	parseenv(char **env, t_env **env_vars, int a)
{
	t_env *e;

	e = NULL;
	while (env[++a])
	{
		if (e)
		{
			e->next = new_env(env[a]);
			if (!e->next)
				return (0);
			e = e->next;
		}
		if (!e)
		{
			e = new_env(env[a]);
			if (!e)
				return (0);
			*env_vars = e;
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**params;
	t_env	*env_vars;

	// for (int i = 0; env[i]; i++)
	// 	printf("%s\n", env[i]);
	parseenv(env, &env_vars, -1); //free if erro malloc
	test(env_vars);
	// while (1)
	// {
	// 	// show_prompt();
	// 	// read_command(input, params);
	// }


	return (0);
}
