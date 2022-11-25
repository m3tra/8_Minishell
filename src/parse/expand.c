/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:18:42 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/25 17:36:24 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*list_get(const char *var, t_env *env)
{
	t_env	*list;
	char	*value;

	list = env;
	while (list && !ft_strcmp(var, list->name))
		list = list->next;
	if (list)
	{
		value = ft_strdup(list->value);
		free(list);
		return (value);
	}
	free(list);
	return (NULL);
}

static char	*replace_str(char *str, char *value, int pos, int len)
{
	char	*temp1;
	char	*temp2;
	int		i;

	temp1 = ft_substr(str, 0, pos);
	i = -1;
	while (value[i])
		value[i] += 132;
	temp2 = ft_strjoin(temp1, value);
	free(value);
	free(temp1);
	temp1 = ft_strjoin(temp2, str + pos + len);
	free(temp2);
	return (temp1);
}

static int	replace(char **str, int start, t_cenas *cmd, int i, int j)
{
	char	*s;
	char	*value;
	char	*var;

	i = start;
	s = *str;
	if (s[i] == '?' || (s[i] - 132) == '?')
		cmd->cmd_flags |= 2;
	if (s[i] == '?' || (s[i] - 132) == '?')
		return (0);
	while (ft_isalnum(s[i]) || (s[i]) == '_' || ft_isalnum(s[i] - 132) || \
		(s[i] - 132) == '_')
		i++;
	i -= start;
	if (!i)
		return (0);
	var = ft_substr(s, start, i);
	unmask_str(var);
	value = list_get(var, g_global.env_list);
	free(var);
	if (!value)
		return (0);
	j = ft_abs(i - ft_strlen(value));
	*str = replace_str(s, value, start - 1, i + 1);
	free(s);
	return (j);
}

static char	*expand_cmd(char *s, t_cenas *cmd)
{
	int	i;

	i = -2;
	if (!s)
		return (NULL);
	while (++i && s[(++i) >> 1])
	{
		(s[i >> 1] == '\'') && (i ^= 1);
		if (i & 1)
			continue ;
		if ((s[i >> 1] & 0x7F) == '$')
			i += (replace(&s, (i >> 1) + 1, cmd, 0, 0) << 1);
		else if (s[i >> 1] == '*')
			i = (wild(i >> 1, &s, cmd, -1) << 1) + (i & 1);
	}
	return (s);
}

int	expand(t_tree *tree)
{
	t_cenas	*cenas;
	int		i;

	cenas = (t_cenas *)tree->content;
	if (cenas)
	{
		cenas->line = expand_cmd(cenas->line, cenas);
		if (!cenas->line)
			return (0);
	}
	i = 0;
	while (i < tree->lcount)
		if (!expand(tree->leafs[i++]))
			return (0);
	return (1);
}
