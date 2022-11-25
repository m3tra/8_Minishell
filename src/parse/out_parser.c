/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:07:05 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/25 15:58:51 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspecial(char a)
{
	return (!!ft_strchr(" \t\n\v\f\r<>$\"\'&|()", a));
}

static int	input(char *str, t_cenas *cmd, int heredoc)
{
	int		j;
	int		k;
	t_list	*list;
	char	*in;

	k = 0;
	j = 0;
	list = NULL;
	while (str[k] && ft_isspace(str[k]))
		k++;
	while (str[k + j] && !ft_isspace(str[k + j]) && !ft_isspecial(str[k + j]))
		j++;
	in = ft_substr(str, k, j);
	if (!heredoc)
		list = ft_lstnew(ft_strjoin("<", in));
	else
		list = ft_lstnew(ft_strjoin("<<", in));
	free(in);
	if (!list)
		return (-1);
	if (heredoc)
		ft_lstadd_back(&cmd->in.heredoc, list);
	else
		ft_lstadd_back(&cmd->in.input, list);
	cmd->in.in = list;
	ft_memset(str - (1 + !!heredoc), ' ', k + j + 1 + !!heredoc);
	return (k + heredoc + !!heredoc);
}

static int	output(char *str, t_cenas *cmd, int append)
{
	int		j;
	int		spc;
	t_list	*list;
	char	*out;

	spc = 0;
	j = 0;
	list = NULL;
	while (str[spc] && ft_isspace(str[spc]))
		spc++;
	while (str[spc + j] && !ft_isspace(str[spc + j]))
		j++;
	out = ft_substr(str, spc, j);
	if (!append)
		list = ft_lstnew(ft_strjoin(">", out));
	else
		list = ft_lstnew(ft_strjoin(">>", out));
	free(out);
	if (!list)
		return (-1);
	if (append)
		ft_lstadd_back(&cmd->in.append, list);
	else
		ft_lstadd_back(&cmd->in.output, list);
	cmd->in.out = list;
	ft_memset(str - (1 + !!append), ' ', spc + j + 1 + !!append);
	return (spc + j + !!append);
}

static int	parse_in_out_cmd(t_cenas *cenas)
{
	char	q;
	char	dq;
	char	*str;
	int		i;

	q = 0;
	dq = 0;
	str = cenas->line;

// //debug
// 	if (str)
// 		printf("cenas->line(%ld): %s\n", ft_strlen(str), str);
// 	else
// 		printf("cenas->line: empty\n");

	while (str)
	{
		if (*str == '\'' && !dq)
			q = !q;
		if (*str == '\"' && !q)
			dq = !dq;
		if (q || dq)
			str++;
		if (q || dq)
			continue ;
		if (*str == '<')
		{
			if (*str + 1 == '<')
				i = input(str + 2, cenas, 1);
			else
				(i = input(str + 1, cenas, 0));
		}
		else if (*str == '>')
		{
			if (*str + 1 == '>')
				i = output(str + 2, cenas, 1);
			else
				i = output(str + 1, cenas, 0);
		}
		else
			i = 0;
		if (i < 0)
			return (0);
		str += i + 1;
	}
	return (1);
}

int	parse_in_out(t_tree *tree)
{
	t_cenas	*cenas;
	int		i;

	// print_tree(tree);

	cenas = tree->cenas;
	if (cenas)
		if (!parse_in_out_cmd(cenas))
			return (0);
	i = 0;
	while (i < tree->lcount)
		if (!parse_in_out(tree->leafs[i++]))
			return (0);
	return (1);
}
