/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:13:57 by fheaton-          #+#    #+#             */
/*   Updated: 2022/07/29 17:29:22 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isempty(const char *str)
{
	int	i;

	i = 0;
	while (str && ft_isspace(str[i]))
		i++;
	return (str && !str[i]);
}

static int	check_qparen(const char *str, char q, char text, char dq, int i)
{
	while (i != -2 && str[++i])
	{
		if (str[i] == '\'' && !dq)
			q = !q;
		if (str[i] == '\"' && !q)
			dq = !dq;
		if (q || dq || ft_isspace(str[i]))
			continue ;
		if (str[i] == '(')
			i = check_qparen(str, 0, 0, 0, i);
		else if (str[i] == ')' && text)
			return (i);
		else if (str[i] == ')')
			return (-2);
		else
			text++;
	}
	if (q)
		return (-2);
	return (i);
}

static int	check_ops(const char *str, char q, char text, char dq, int i)
{
	int	paren;
	
	paren = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !dq)
			q = !q;
		if (str[i] == '\'' && !dq)
			text = 1;
		if (str[i] == '\"' && !q)
			dq = !dq;
		if (str[i] == '\"' && !q)
			text = 1;
		if (q || dq || ft_isspace(str[i]))
			continue ;
		if (((str[i] == '&' && str[i + 1] == '&')
				|| (str[i] == '|' && str[i + 1] == '|') || (str[i] == ';')))
		{
			if ((!text && paren != 8) || (text && paren == 8))
				return (0);
			if (str[i] != ';')
				++i;
			text = 0;
		}
		else if (str[i] == ')' && ((text && !(paren == 8)) || (!text && (paren == 8))))
			(text || !text) && (paren = 8)
				&& (text = 0);
		else if (str[i] == '(' && !text && !(paren == 8))
			paren = 4;
		else if (str[i] == '(' || str[i] == ')')
			return (0);
		else
			text = 1;
	}
	return ((text && q != 8) || (!text && q == 8));
}

t_commands	*check_input(const char *str)
{
	t_commands *cmd;

	cmd = ft_calloc(1, sizeof(t_commands));
	if (!cmd)
		return (NULL);
	if (!str || isempty(str))
		return (NULL);
	if (check_qparen(str, 0, 0, 0, -1) != (int)ft_strlen(str))
		return (NULL);
	else if (!check_ops(str, 0, 0, 0, -1))
		return (NULL);
	return (cmd);
}
