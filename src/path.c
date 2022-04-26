/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:53:27 by fporto            #+#    #+#             */
/*   Updated: 2022/04/26 01:20:57 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_value(void)
{
	t_env	*ret;

	ret = g_global.env_list;
	while (ret)
	{
		if (!ft_strcmp(ret->name, "PATH"))
			break ;
		ret = ret->next;
	}
	return (ret->value);
}

static int	isolate_various_paths(char **path_var)
{
	int			nb_colons;
	const char	*orig_path_var;
	int			j;

	orig_path_var = get_path_value();
	if (orig_path_var)
		*path_var = ft_strdup(orig_path_var);
	else
		*path_var = ft_strdup("");
	nb_colons = 0;
	j = -1;
	while (++j < (int)ft_strlen(*path_var))
	{
		if (*path_var[j] == ':')
		{
			nb_colons++;
			*path_var[j] = '\0';
		}
	}
	return (nb_colons);
}

void	parse_path()
{
	char	**ret;
	char	*path_var;
	int		nb_colons;
	int		current_colon;
	int		j;

	nb_colons = isolate_various_paths(&path_var);
	ret = malloc(sizeof(*ret) * (nb_colons + 1));
	if (!ret)
		free_global("Failed malloc");
	ret[0] = path_var;
	current_colon = 0;
	j = -1;
	while (++j < (int)ft_strlen(path_var))
	{
		if (path_var[j] == '\0')
		{
			current_colon++;
			ret[current_colon] = path_var + j + 1;
			if (ret[current_colon][0] == '\0')
				ret[current_colon] = ".";
		}
	}
	j = -1;
	while (++j < nb_colons + 1)
		printf("Path %d: <%s>\n", j, ret[j]);
	g_global.path_dirs = ret;
}
