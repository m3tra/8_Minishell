/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:53:27 by fporto            #+#    #+#             */
/*   Updated: 2022/11/25 15:46:22 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_path_value(void)
// {
// 	t_env	*ret;

// 	ret = g_global.env_list;
// 	while (ret)
// 	{
// 		if (!ft_strcmp(ret->name, "PATH"))
// 			break ;
// 		ret = ret->next;
// 	}
// 	return (ret->value);
// }

// static int	isolate_various_paths(char **path_var)
// {
// 	int			nb_colons;
// 	const char	*orig_path_var;
// 	int			j;

// 	orig_path_var = get_path_value();
// 	if (orig_path_var)
// 		*path_var = ft_strdup(orig_path_var);
// 	else
// 		*path_var = ft_strdup("");
// 	nb_colons = 0;
// 	j = -1;
// 	while (++j < (int)ft_strlen(*path_var))
// 	{
// 		if (*path_var[j] == ':')
// 		{
// 			nb_colons++;
// 			*path_var[j] = '\0';
// 		}
// 	}
// 	return (nb_colons);
// }

// void	parse_path()
// {
// 	char	**ret;
// 	char	*path_var;
// 	int		nb_colons;
// 	int		current_colon;
// 	int		j;

// 	nb_colons = isolate_various_paths(&path_var);
// 	ret = malloc(sizeof(*ret) * (nb_colons + 1));
// 	if (!ret)
// 		free_global("Failed malloc");
// 	ret[0] = path_var;
// 	current_colon = 0;
// 	j = -1;
// 	while (++j < (int)ft_strlen(path_var))
// 	{
// 		if (path_var[j] == '\0')
// 		{
// 			current_colon++;
// 			ret[current_colon] = path_var + j + 1;
// 			if (ret[current_colon][0] == '\0')
// 				ret[current_colon] = ".";
// 		}
// 	}
// 	j = -1;
// 	while (++j < nb_colons + 1)
// 		printf("Path %d: <%s>\n", j, ret[j]);
// 	g_global.path_dirs = ret;
// }

// Returns full path
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

// Returns number of separating ':' chars
size_t	count_colons(char *str)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (str[i])
		if (str[i++] == ':')
			n++;
	return (n);
}

// Returns a string with every ':' separator changed to '\0'
char	*sub_colons(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			str[i] = '\0';
		i++;
	}
	return (str);
}

// Returns an array with every '\0' separated string
char	**isolate_strings(char *str, size_t nb_colons)
{
	char	**ret;
	size_t	i;
	char	*single_str;
	size_t	ptr_shift;

	ret = malloc(sizeof(char *) * (nb_colons + 2));
	if (!ret)
		free_global("Failed malloc");
	i = 0;
	while (i < nb_colons + 1)
	{
		single_str = ft_strdup(str);
		// printf("\t%s\n", single_str);
		ret[i] = single_str;
		ptr_shift = ft_strlen(single_str) + 1;
		str += ptr_shift;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	parse_path(void)
{
	char	**ret;
	// char	*path_var;
	// int		current_colon;
	// int		j;
	char	*orig_path;
	// size_t	path_len;
	size_t	nb_colons;
	char	*subd_path;

	orig_path = get_path_value();
	g_global.path = orig_path;
	// printf("orig_path: %s\n", orig_path);
	// path_len = ft_strlen(orig_path);
	nb_colons = count_colons(orig_path);
	subd_path = sub_colons(orig_path);



	ret = isolate_strings(subd_path, nb_colons);

	g_global.path_dirs = ret;
}
