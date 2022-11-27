/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:18 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/27 19:24:42 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_in_out(void *v)
{
	t_cenas	*cmd;

	if (!v)
		return ;
	cmd = (t_cenas *)v;
	if (cmd->in.input)
		ft_lstclear(&cmd->in.input, free);
	if (cmd->in.output)
		ft_lstclear(&cmd->in.output, free);
	if (cmd->in.heredoc)
		ft_lstclear(&cmd->in.heredoc, free);
	if (cmd->in.append)
		ft_lstclear(&cmd->in.append, free);
}

static void	free_cmd(void *v)
{
	t_cenas	*cmd;
	int		i;

	if (!v)
		return ;
	cmd = (t_cenas *)v;
	if (cmd->line)
		free(cmd->line);
	i = -1;
	if (cmd->cmd)
	{
		while (cmd->cmd[++i])
			free(cmd->cmd[i]);
		free(cmd->cmd);
	}
	if (cmd->in.input || cmd->in.output || cmd->in.heredoc || \
		cmd->in.append || cmd->in.in || cmd->in.out)
		free_in_out(v);
	free(v);
}

void	free_command(t_commands *cmd)
{
	if (!cmd)
		return ;
	free(cmd->line);
	treeclear(cmd->tree, free_cmd);
	free(cmd);
}

t_full_cmd	*parse(char	*input)
{
	t_commands	*cmd;
	t_full_cmd	*full_cmd;
	int			err;

	err = 0;
	cmd = check_input(input);
	if (!cmd)
		return (NULL);
	cmd->tree = treenew(NULL);
	cmd->line = parse_q(ft_strdup(input), 0);
	if ((split_cmd(cmd->tree, cmd->line, 0) - 1) == (int)ft_strlen(cmd->line))
		return (NULL);
	if (!parse_op(cmd->tree))
		return (NULL);
	if (!expand(cmd->tree))
		return (NULL);
	if (!word_split(cmd->tree))
		err = 1;
	// print_tree(cmd->tree);
	if (!err)
		unmask(cmd->tree);
	full_cmd = initialize_struct(cmd);
	full_cmd->curr_simple_cmd = full_cmd->simple_cmds[0];
	// free_tree(cmd->tree);
	free_command(cmd);
	if (!full_cmd)
		return (NULL);
	return (full_cmd);
}
