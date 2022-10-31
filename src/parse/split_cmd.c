/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:45:02 by fheaton-          #+#    #+#             */
/*   Updated: 2022/10/30 13:42:48 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	*newcmd(char *key, char *c)
{
	t_cenas	*cmd;
	t_flags	*cmd_flags;

	cmd = ft_calloc(1, sizeof(t_cenas));
	if (!cmd)
		return (NULL);
	cmd_flags = ft_calloc(1, sizeof(t_flags));
	if (!cmd_flags)
		return (NULL);
	cmd->line = c;
	if (!ft_strncmp(key, "&&", 2))
		cmd_flags->and = 1;
	else if (!ft_strncmp(key, "||", 2))
		cmd_flags->or = 1;
	else if (*key == ')' || *key == '\0')
		cmd_flags->endList = 1;
	else if (*key == ';')
		cmd_flags->resLogic += 1;
	else if (*key == '|')
		cmd_flags->pipe = 1;
	if (cmd_flags->and != 0 || cmd_flags->or != 0 || cmd_flags->endList != 0 ||
	 cmd_flags->resLogic != 0 || cmd_flags->pipe != 0)
		cmd->cmd_flags = cmd_flags;
	else
		free (cmd_flags);
	return (cmd);
}

int	split_cmd(t_tree *tree, char *line, int i)
{
	int j;
	
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
		treeadd(tree, newcmd(line + i, ft_substr(line, i, i - j)));
	if (j == -1 || !line[i])
		return (i);
	return (i + 1);
}
