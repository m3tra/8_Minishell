/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:57 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/27 18:24:28 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	inout_flags(t_cenas *cmd, t_simple_cmd	*simple)
{
	simple->inout = cmd->in;
	if (cmd->in.input && cmd->in.input->content)
	{
		simple->_input_file = (char *)ft_lstlast(cmd->in.input)->content;
		simple->heredoc = 0;
	}
	if (cmd->in.heredoc && cmd->in.heredoc->content)
	{
		simple->_input_file = (char *)ft_lstlast(cmd->in.heredoc)->content;
		simple->heredoc = 1;
	}
	if (cmd->in.output && cmd->in.output->content)
	{
		simple->_out_file = (char *)ft_lstlast(cmd->in.output)->content;
		simple->append = 0;
	}
	if (cmd->in.append && cmd->in.append->content)
	{
		simple->_out_file = (char *)ft_lstlast(cmd->in.append)->content;
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

void	initialize_simple(t_full_cmd *full_cmd, t_tree	*t)
{
	t_simple_cmd	**simple;
	int				i;

	simple = ft_calloc(t->lcount, sizeof(t_simple_cmd *));
	if (!simple)
		return ;
	i = -1;

	while (++i < t->lcount)
	{
		simple[i] = malloc(sizeof(t_simple_cmd));
		if (!simple[i])
			return ;
		if (!cmd_cpy(simple[i], t->leafs[i]))
			return ;
	}
	full_cmd->simple_cmds = simple;
}

t_full_cmd	*initialize_struct(t_commands *cmd)
{
	t_full_cmd	*full_cmd;

	full_cmd = calloc(1, sizeof(t_full_cmd));
	if (!full_cmd)
		return (NULL);
	full_cmd->n_simple_cmds = cmd->tree->lcount;
	initialize_simple(full_cmd, cmd->tree);
	full_cmd->curr_simple_cmd = full_cmd->simple_cmds[0];
	return (full_cmd);
}
