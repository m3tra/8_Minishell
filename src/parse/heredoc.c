/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 22:52:39 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 01:19:57 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	realoc_str(t_cenas	*cenas, char *input)
{
	char	**str;
	int		i;
	
	i = 0;
	while (cenas->cmd[i])
		i++;
	str = cenas->cmd;
	printf("i: %d\n", i);
	cenas->cmd = malloc((i + 2) * sizeof(char *));
	if(!cenas->cmd)
		return (0);
	i = -1;
	while (str[++i])
	{
		cenas->cmd[i] = ft_strdup(str[i]);
		free(str[i]);
		printf("str[%d]: %s\n", i, cenas->cmd[i]);
	}
	free(str);
	cenas->cmd[i] = ft_strdup(input);
	cenas->cmd[i + 1] = NULL;
	return (1);
}

static int	read_hrdoc(char *eof, t_cenas *cenas)
{
	char	*input;
	int		i;

	input = readline("heredoc> ");
	if (!eof)
		return (-1);
	while (input && ft_strcmp(input, eof))
	{
		if (ft_strlen(input) > 0)
			i = realoc_str(cenas, input);
		if (!i)
			return (-1);
		ft_free(input);
		input = readline("heredoc> ");
	}
	ft_free(input);
	ft_free(eof);

	return (0);
}

int	check_heredoc_call(t_tree *t)
{
	t_list	*head;
	char	*eof;
	t_cenas	*cenas;

	cenas = (t_cenas *)t->content;
	eof = NULL;
	if (cenas->in.heredoc)
		head = cenas->in.heredoc;
	while (cenas->in.heredoc)
	{
		eof = (char *)cenas->in.heredoc->content;
		if (read_hrdoc(ft_substr(eof, 2, ft_strlen(eof)), cenas) < 0)
		{
			printf("Error: unable to read heredoc\n");
			return (0);
		}
		cenas->in.heredoc = cenas->in.heredoc->next;
	}
	if (eof)
		cenas->in.heredoc = head;
	return (1);
}


void	check_heredoc(t_tree *t)
{
	int	i;
	int	ret;
	
	i = -1;
	ret = 1;
	while (++i < t->lcount)
	{
		ret = check_heredoc_call(t->leafs[i]);
		if (ret == 0 && t->leafs[i])
			check_heredoc(t->leafs[i]);
	}
}
