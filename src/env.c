/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:12:47 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 22:01:35 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env_vars)
{
	t_env	*tmp;

	while (env_vars)
	{
		ft_free(env_vars->name);
		ft_free(env_vars->value);
		tmp = env_vars->next;
		free(env_vars);
		env_vars = tmp;
	}
}

static int	ft_strlenchar(const char *str, char character)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != character)
		i++;
	return (i);
}

static t_env	*new_env(char *env)
{
	t_env	*t;
	int		name;
	int		value;

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

t_env	*parse_env(char **env, int a)
{
	t_env	*e;
	t_env	*tmp;

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
