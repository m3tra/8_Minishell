/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:57 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 01:28:23 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	inout_flags(t_cenas *cmd, t_simple_cmd	*simple)
{
	simple->inout = cmd->in;
	simple->_out_file = NULL;
	simple->_input_file = NULL;
	if (cmd->in.input && cmd->in.input->content)
	{
		simple->_input_file = ft_strdup(ft_lstlast(cmd->in.input)->content);
		simple->heredoc = 0;
	}
	if (cmd->in.heredoc && cmd->in.heredoc->content)
	{
		simple->_input_file = ft_strdup(ft_lstlast(cmd->in.heredoc)->content);
		simple->heredoc = 1;
	}
	if (cmd->in.output && cmd->in.output->content)
	{
		simple->_out_file = ft_strdup(ft_lstlast(cmd->in.output)->content);
		simple->append = 0;
	}
	if (cmd->in.append && cmd->in.append->content)
	{
		simple->_out_file = ft_strdup(ft_lstlast(cmd->in.append)->content);
		simple->append = 1;
	}
	if (cmd->cmd_flags & 0x40)
		simple->pipe = 1;
	else
		simple->pipe = 0;
}

int	cmd_cpy(t_simple_cmd *simple, t_tree *tree)
{
	t_cenas	*cenas;
	int		i;

	cenas = (t_cenas *)tree->content;
	i = 0;
	while (cenas->cmd[i])
		i++;
	simple->args = malloc((i + 1) * sizeof(char *));
	if (!simple->args)
		return (0);
	i = -1;
	while (cenas->cmd[++i])
		simple->args[i] = ft_strdup(cenas->cmd[i]);
	simple->n_args = i;
	simple->args[i] = NULL;
	inout_flags(cenas, simple);
	return (1);
}

int	initialize_simple(t_full_cmd *full_cmd, t_tree	*t)
{
	t_simple_cmd	**simple;
	int				i;

	simple = ft_calloc(t->lcount, sizeof(t_simple_cmd *));
	if (!simple)
		return (0);
	i = -1;
	while (++i < t->lcount)
	{
		simple[i] = malloc(sizeof(t_simple_cmd));
		if (!simple[i])
			return (0);
		if (!cmd_cpy(simple[i], t->leafs[i]))
			return (0);
	}
	full_cmd->simple_cmds = simple;
	return (1);
}

t_full_cmd	*initialize_struct(t_commands *cmd)
{
	t_full_cmd	*full_cmd;

	full_cmd = calloc(1, sizeof(t_full_cmd));
	if (!full_cmd)
		return (NULL);
	full_cmd->n_simple_cmds = cmd->tree->lcount;
	if (!initialize_simple(full_cmd, cmd->tree))
	{
		free (full_cmd);
		return (NULL);
	}
	full_cmd->curr_simple_cmd = full_cmd->simple_cmds[0];
	return (full_cmd);
}
