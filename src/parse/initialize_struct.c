/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:57 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/26 15:29:35 by fheaton-         ###   ########.fr       */
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
	printf("TEST cmd_cpy\n");
	printf("simple: %p, tree: %p\n", simple, tree);
	t_cenas	*cenas;
	int		i;

	if (!tree->leafs)
		printf("TEST NO LEAFS\n");

	cenas = (t_cenas *)tree->content;
	i = 0;
	while (cenas->cmd[i])
		i++;
	simple->args = malloc(i * sizeof(char *));
	if (!simple->args)
		return (0);
	i = -1;


	while (cenas->cmd[++i])
		simple->args[i] = ft_strdup(cenas->cmd[i]);
	// printf("test simple->args[0]: %s\n", simple->args[0]);
	inout_flags(cenas, simple);
	return (1);
}

void	initialize_simple(t_full_cmd *full_cmd, t_tree	*t)
{
	printf("TEST initialize_simple\n");

	t_simple_cmd	**simple;
	int				i;

	simple = ft_calloc(t->lcount, sizeof(t_simple_cmd *));
	if (!simple)
		return ;
	i = -1;

	while (++i < t->lcount)
	{
		printf("TEST t->lcount: %d\n", t->lcount);
		simple[i] = malloc(sizeof(t_simple_cmd));
		if (!simple[i])
			return ;
		if (!cmd_cpy(simple[i], t->leafs[i]))
			return ;
	}
	printf("test simple->args[0]: %s\n", simple[0]->args[0]);
	full_cmd->simple_cmds = simple;
}

t_full_cmd	*initialize_struct(t_commands *cmd)
{
	// printf("TEST initialize_struct\n");
	t_full_cmd	*full_cmd;

	full_cmd = calloc(1, sizeof(t_full_cmd));
	if (!full_cmd)
		return (NULL);
	full_cmd->n_simple_cmds = cmd->tree->lcount;

	printf("test n_simple_cmds: %d\n", full_cmd->n_simple_cmds);

	initialize_simple(full_cmd, cmd->tree);

	if (!full_cmd->simple_cmds[0])
		printf("simple_cmds = NULL\n");
	full_cmd->curr_simple_cmd = full_cmd->simple_cmds[0];
	return (full_cmd);
}
