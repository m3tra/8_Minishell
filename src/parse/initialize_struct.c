/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:57 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/20 00:59:40 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "struct.h"

void	inout_flags(t_cenas *cmd, t_simple_cmd	*simple)
{
	if (cmd->in.input)
	{
		simple->_inputFile = ft_strdup((char *)cmd->in.input->content);
		simple->heredoc = 0;
	}
	if (cmd->in.heredoc)
	{
		simple->_inputFile = ft_strdup((char *)cmd->in.input->content);
		simple->heredoc = 1;
	}
	if (cmd->in.output)
	{
		simple->_outFile = ft_strdup((char *)cmd->in.output->content);
		simple->append = 0;
	}
	if (cmd->in.append)
	{
		simple->_outFile = ft_strdup((char *)cmd->in.output->content);
		simple->append = 1;
	}
}

int	cmd_cpy(t_simple_cmd	*simple, t_tree *t)
{
	t_cenas			*cmd;
	char			**args;
	int				i;

	cmd = (t_cenas	*)t->content;
	i = 0;
	while (cmd->cmd[i])
		i++;
	args = malloc(i * sizeof(char *));
	if (!args)
		return (0);
	i = -1;
	while(cmd->cmd[++i])
		simple->args[i] = ft_strdup(cmd->cmd[i]);
	inout_flags(cmd, simple);
	return (1);
}

t_simple_cmd	**initialize_simple(t_tree	*t)
{
	t_simple_cmd	**simple;
	int				i;

	simple = malloc(t->lcount * sizeof(t_simple_cmd *));
	if (!simple)
		return (NULL);
	i = -1;
	while (++i < t->lcount)
	{
		if (!cmd_cpy(simple[i], t->leafs[i]))
			return (NULL);
	}
	return (simple);
}

t_cmd	*initialize_struct(t_commands *cmd)
{
	t_cmd			*cenas;

	cenas = calloc(1, sizeof(t_cmd));
	if (!cenas)
		return (NULL);
	cenas->nSimpleCmds = cmd->tree->lcount;
	cenas->simpleCmds = initialize_simple(cmd->tree);
	cenas->currSimpleCmd = *cenas->simpleCmds;
	return (cenas);
}
