/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:57 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/25 20:48:01 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "struct.h"

void	inout_flags(t_cenas *cmd, t_simple_cmd	*simple)
{
	if (cmd->in.input)
	{
		simple->_input_file = ft_strdup((char *)cmd->in.input->content);
		simple->heredoc = 0;
	}
	if (cmd->in.heredoc)
	{
		simple->_input_file = ft_strdup((char *)cmd->in.input->content);
		simple->heredoc = 1;
	}
	if (cmd->in.output)
	{
		simple->_out_file = ft_strdup((char *)cmd->in.output->content);
		simple->append = 0;
	}
	if (cmd->in.append)
	{
		simple->_out_file = ft_strdup((char *)cmd->in.output->content);
		simple->append = 1;
	}
}

int	cmd_cpy(t_simple_cmd *simple, t_tree *tree)
{
	t_cenas	*cenas;
	int		i;

	cenas = (t_cenas *)tree->leafs[0]->content;
	i = 0;
	while (cenas->cmd[i])
		i++;
	simple->args = malloc(i * sizeof(char *));
	if (!simple->args)
		return (0);
	i = -1;
	while (cenas->cmd[++i])
		simple->args[i] = ft_strdup(cenas->cmd[i]);
	inout_flags(cenas, simple);
	return (1);
}

t_simple_cmd	**initialize_simple(t_tree	*t)
{
	t_simple_cmd	**simple;
	int				i;

	simple = ft_calloc(t->lcount, sizeof(t_simple_cmd *));
	if (!simple)
		return (NULL);
	i = -1;
	while (++i < t->lcount - 1)
	{
		if (!cmd_cpy(simple[i], t->leafs[i]))
			return (NULL);
	}
	return (simple);
}

t_full_cmd	*initialize_struct(t_commands *cmd)
{
	t_full_cmd	*cenas;

	cenas = calloc(1, sizeof(t_full_cmd));
	if (!cenas)
		return (NULL);
	cenas->n_simple_cmds = cmd->tree->lcount;
	cenas->simple_cmds = initialize_simple(cmd->tree);
	cenas->curr_simple_cmd = *cenas->simple_cmds;
	return (cenas);
}
