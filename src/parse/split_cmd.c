/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:45:02 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/27 11:32:52 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	*newcmd(char *key, char *line)
{
	t_cenas	*cenas;

	cenas = ft_calloc(1, sizeof(t_cenas));
	if (!cenas)
		return (NULL);
	cenas->line = line;
	// cenas->in.in = NULL;
	// cenas->in.input = NULL;
	// cenas->in.heredoc = NULL;
	// cenas->in.out = NULL;
	// cenas->in.output = NULL;
	// cenas->in.append = NULL;
	((!ft_strncmp(key, "&&", 2)) && (cenas->cmd_flags |= 0x04))
	|| ((!ft_strncmp(key, "||", 2)) && (cenas->cmd_flags |= 0x08))
	|| (((*key == ')') || (*key == '\0')) && (cenas->cmd_flags |= 0x10))
	|| ((*key == ';') && (cenas->cmd_flags |= 0x20))
	|| ((*key == '|') && (cenas->cmd_flags |= 0x40));
	return (cenas);
}

int	split_cmd(t_tree *tree, char *line, int i)
{
	int	j;

	j = i;
	while (j >= 0 && line[i] && line[i] != ')')
		((((line[i] == '&') || (line[i] == '|')) && (line[i] == line[i + 1]))
			&& (treeadd(tree, newcmd(line + i, ft_substr(line, j, i - j))))
			&& (i += 2) && (j = i))
		|| ((line[i] == '(') && (treeadd(tree, NULL))
			&& (i = split_cmd(tree->leafs[tree->lcount - 1], line, i + 1))
			&& (j = i))
		|| ((line[i] == ';')
			&& (treeadd(tree, newcmd(line + i, ft_substr(line, j, i - j))))
			&& (i = split_cmd(tree, line, i + 1)) && (j = -1))
		|| ((line[i] == '|')
			&& (treeadd(tree, newcmd(line + i, ft_substr(line, j, i - j))))
			&& (j = ++i))
		|| (i++);
	if (j >= 0 && i - j > 0)
		treeadd(tree, newcmd(line + i, ft_substr(line, j, i - j)));
	if (j == -1 || !line[i])
		return (i);
	return (i + 1);
}
