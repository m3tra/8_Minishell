/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:58:18 by fheaton-          #+#    #+#             */
/*   Updated: 2022/10/30 12:26:39 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_in_out(void *v)
{
	t_cmd	*cmd;

	if	(!v)
		return ;
	cmd = (t_cmd *)v;
	if (cmd->in.input)
		ft_lstclear(&cmd->in.input, free);
	if (cmd->in.output)
		ft_lstclear(&cmd->in.output, free);
	if (cmd->in.heredoc)
		ft_lstclear(&cmd->in.heredoc, free);
	if (cmd->in.append)
		ft_lstclear(&cmd->in.append, free);
	if (cmd->in.in)
		ft_lstclear(&cmd->in.in, free);
	if (cmd->in.out)
		ft_lstclear(&cmd->in.out, free);

}

static void	free_cmd(void *v)
{
	t_cmd	*cmd;
	int		i;

	if	(!v)
		return ;
	cmd = (t_cmd *)v;
	if (cmd->line)
		free(cmd->line);
	i = -1;
	if (cmd->cmd)
	{
		while (cmd->cmd[++i])
			free(cmd->cmd[i]);
		free(cmd->cmd);
	}
	if (cmd->cmd_flags)
		free(cmd->cmd_flags)
	if (cmd->in.input || cmd->in.output || cmd->in.heredoc ||
	 cmd->in.append || cmd->in.in || cmd->in.out)
	 	free_in_out(v);
	free(v);
}

void	free_command(t_commands *cmd)
{
	free(cmd->line);
	ft_treeclear(cmd->tree, free_cmd);
	free(cmd);
}

t_commands	*parse(char	*input)
{
	t_commands	*cmd;
	t_cmd		*cenas;
	int err;

	err = 0;
	cmd = check_input(input);
	if (!cmd)
		return (NULL);
	cmd->tree = treenew(NULL);
	cmd->line = parse_q(ft_strdup(input), 0, cmd);
	if ((split_cmd(cmd->tree, cmd->line, 0) - 1) == (int)ft_strlen(cmd->line))
		return (NULL);
	if (!parse_in_out(cmd->tree))
		return (NULL);
	if (!expand(cmd->tree))
		return (NULL);
	// // if (!word_split(cmd->tree))
	// // 	err = 1;
	// if (!err)
	// 	unmask(cmd->tree);
	cenas = initialize_struct(cmd);
	if (!cenas)
		return (NULL);
	return (cenas);
	
}