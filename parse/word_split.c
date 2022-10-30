/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:48:33 by fheaton-          #+#    #+#             */
/*   Updated: 2022/10/18 16:48:55 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"

int	word_split(t_tree *t)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)t->content;
	if (cmd)
		cmd->cmd = ft_split(cmd->line, ' ');
	i = 0;
	while (i < t->lcount)
		if (!word_split(t->leafs[i++]))
			return (0);
	return (1);
}
