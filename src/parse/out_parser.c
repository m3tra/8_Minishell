/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:07:05 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/27 20:19:57 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspecial(char a)
{
	return (!!ft_strchr(" \t\n\v\f\r<>$\"\'&|()", a));
}

static int	input(char *s, t_cenas *cmd, int heredoc)
{
	int		i;
	int		skp;
	t_list	*l;
	char	*in;

	skp = 0;
	i = 0;
	l = NULL;
	while (s[skp] && ft_isspace(s[skp + i]))
		skp++;
	while (s[skp + i] && !ft_isspace(s[skp + i]) && !ft_isspecial(s[skp + i]))
		i++;
	in = ft_substr(s, skp, i);
	((!heredoc) && (l = ft_lstnew(ft_strjoin("<", in))))
		|| (l = ft_lstnew(ft_strjoin("<<", in)));
	free(in);
	if (!l)
		return (-1);
	if (heredoc)
		ft_lstadd_back(&cmd->in.heredoc, l);
	else
		ft_lstadd_back(&cmd->in.input, l);
	cmd->in.in = l;
	ft_memset(s - (1 + !!heredoc), ' ', skp + i + 1 + !!heredoc);
	return (skp + i + !!heredoc);
}

static int	output(char *str, t_cenas *cmd, int append)
{
	int		i;
	int		skip;
	t_list	*l;
	char	*out;

	skip = 0;
	i = 0;
	l = NULL;
	while (str[skip] && ft_isspace((int)str[skip]))
		skip++;
	while (str[skip + i] && !ft_isspace(str[skip + i]))
		i++;
	out = ft_substr(str, skip, i);
	((!append) && (l = ft_lstnew(ft_strjoin("", out))))
		|| (l = ft_lstnew(ft_strjoin("", out)));
	free(out);
	if (!l)
		return (-1);
	if (append) {
		ft_lstadd_back(&cmd->in.append, l);
	}
	else
		ft_lstadd_back(&cmd->in.output, l);
	cmd->in.out = l;
	ft_memset(str - (1 + !!append), ' ', skip + i + 1 + !!append);
	return (skip + i + !!append);
}

static int	parse_op_cmd(t_cenas *cmd)
{
	char	q;
	char	*cur;
	int		i;

	q = 0;
	cur = (char *) cmd->line;
	while (*cur)
	{
		(*cur == '\'') && !(q & 2) && (q ^= 1);
		(*cur == '\"') && !(q & 1) && (q ^= 2);
		(q & 3) && cur++;
		if (q & 3)
			continue ;
		((!ft_strncmp(cur, "<<", 2)) && ((i = input(cur + 2, cmd, 1) &&
			get_heredoc(cmd, cur)) || 1))
		|| ((!ft_strncmp(cur, ">>", 2)) && ((i = output(cur + 2, cmd, 1)) || 1))
		|| ((*cur == '<') && ((i = input(cur + 1, cmd, 0)) || 1))
		|| ((*cur == '>') && ((i = output(cur + 1, cmd, 0)) || 1))
		|| (i = 0);
		if (i < 0)
			return (0);
		cur += i + 1;
	}
	return (1);
}

int	parse_op(t_tree *t)
{
	t_cenas	*cmd;
	int		i;

	cmd = (t_cenas *)t->content;
	if (cmd)
		if (!parse_op_cmd(cmd))
			return (0);
	i = 0;
	while (i < t->lcount)
		if (!parse_op(t->leafs[i++]))
			return (0);
	return (1);
}
