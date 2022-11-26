/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:57 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/26 14:23:57 by fporto           ###   ########.fr       */
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

	t_cenas	*cenas;
	int		i;

	if (!tree->leafs)
		printf("TEST NO LEAFS\n");

	cenas = (t_cenas *)tree->leafs[0]->content;

	i = 0;
	while (cenas->cmd[i])
		i++;
	simple->args = malloc(i * sizeof(char *));
	if (!simple->args)
		return (0);
	i = -1;

	printf("test cenas->cmd[0]: %s\n", cenas->cmd[0]);

	while (cenas->cmd[++i])
		simple->args[i] = ft_strdup(cenas->cmd[i]);
	inout_flags(cenas, simple);
	return (1);
}

t_simple_cmd	**initialize_simple(t_tree	*t)
{
	printf("TEST initialize_simple\n");

	t_simple_cmd	**simple;
	int				i;

	simple = ft_calloc(t->lcount, sizeof(t_simple_cmd *));
	if (!simple)
		return (NULL);
	i = -1;

	printf("TEST t->lcount: %d\n", t->lcount);

	// while (++i < t->lcount - 1)
	while (++i < t->lcount)
	{
		if (!cmd_cpy(simple[i], t->leafs[i]))
			return (NULL);
	}
	return (simple);
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

	full_cmd->simple_cmds = initialize_simple(cmd->tree);

	if (!full_cmd->simple_cmds)
		printf("simple_cmds = NULL\n");

	full_cmd->curr_simple_cmd = *full_cmd->simple_cmds;
	return (full_cmd);
}
