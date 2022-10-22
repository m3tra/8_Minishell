/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:45:02 by fheaton-          #+#    #+#             */
/*   Updated: 2022/10/22 17:36:19 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*newcmd(char *key, char *c)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->line = c;
	((!ft_strncmp(key, "&&", 2)) && (cmd->cmd_flags |= 0x04))
	|| ((!ft_strncmp(key, "||", 2)) && (cmd->cmd_flags |= 0x08))
	|| (((*key == ')') || (*key == '\0')) && (cmd->cmd_flags |= 0x10))
	|| ((*key == ';') && (cmd->cmd_flags |= 0x20))
	|| ((*key == '|') && (cmd->cmd_flags |= 0x40));
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
			&& (i = split_cmd(t->leafs[tree->lcount - 1], line, i + 1)) && (j = i))
		|| ((line[i] == ';')
			&& (treeadd(t, newcmd(line + i, ft_substr(line, j, i - j))))
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
