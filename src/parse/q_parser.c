/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:48:08 by fheaton-          #+#    #+#             */
/*   Updated: 2022/10/30 16:27:43 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	unmask_str(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		// if (str[i] >= 132)
		// 	str[i] -= 132;
		// if (str[i] == D)
		// 	str[i] = '$';
	}
	return (1);
}

int	unmask(t_tree *t)
{
	t_cenas	*cmd;
	int		i;

	cmd = (t_cenas *)t->content;
	i = -1;
	if (cmd && cmd->line)
		unmask_str(cmd->line);
	if (cmd && cmd->cmd)
		while (cmd->cmd[++i])
			if (!unmask_str(cmd->cmd[i]))
				return (0);
	i = 0;
	while (i < t->lcount)
		if (!unmask(t->leafs[i++]))
			return (0);
	return (1);
}

static char	*remove_q(char *str, int count)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(str) - count + 1, 1);
	i = -1;
	j = -1;
	while (str[++i])
		if (!ft_strchr("\\\"\'", str[i]))
			new[++j] = str[i];
	ft_free(str);
	return (new);
}

char	*parse_q(char *str, int count)
{
	int	q;
	int	dq;
	int	skip;
	int in_var;
	int	i;

	q = 0;
	dq = 0;
	in_var = 0;
	i = -1;
	while(str[++i])
	{
		skip = 0;
		if (str[i] == '\'' && !dq)
		{
			q = !q;
			skip = !skip;
			count++;
		}
		if (str[i] == '\"' && !q)
		{
			dq = !dq;
			skip = !skip;
			count++;
		}
		if (str[i] == '$' && !q)
			in_var = 1;
		else if (ft_strchr(" \'\"\\;&|", str[i]))
			in_var = 0;
		else if (str[i] == '$' && q)
			str[i] = 128;
		else if ((str[i] == '\\') && !q)
		{
			if (ft_strchr("\\\"$", str[i + 1]))
			{
				str++;
				count++;
				if (str[i + 1] == '$')
					str[i] = D;
				else if (str[i + 1] == '\"')
					str[i] = DQ;
				else if (str[i + 1] == '\\')
					str[i] = B;
			}
		}
		else if (str[i] < 128 && (q || dq) && !skip)
			str[i] += 132;
	}
	if (q || dq)
		return (NULL);
	return (remove_q(str, count));
}

