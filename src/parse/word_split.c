/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:48:33 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/27 20:24:51 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_heredoc(t_cenas *cenas, char *line)
{
	char *eof;

	eof = get_word(line);
}

int	word_split(t_tree *tree)
{
	t_cenas	*cenas;
	int		i;
	
	cenas = (t_cenas *)tree->content;
	if (cenas)
		cenas->cmd = ft_split(cenas->line, ' ');
	i = 0;
	while (i < tree->lcount)
		if (!word_split(tree->leafs[i++]))
			return (0);
	return (1);
}
