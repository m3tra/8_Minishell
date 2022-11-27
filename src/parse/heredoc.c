/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:27:20 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/27 21:01:29 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*temp_path(char *filename)
{
	char	*pth;

	if (!filename)
		return (NULL);
	pth = ft_strjoin(path, filename);
	ft_free(g_global.hdoc_files[g_global.file_counter]);
	g_global.hdoc_files[g_global.file_counter++] = filename;
	return (pth);
}

static int	create_hrdoc_file(char *eof, char *filename)
{
	char	*input;
	int		output;

	if (!eof)
		return (-1);
	filename = temp_path(filename);
	if (!filename)
		return (-1);
	output = open(filename, 02 | 0100 | 01000, 0400 | 0200 | 040 | 04);
	if (output < 0)
		return (-1);
	input = readline("> ");
	while (input && ft_strcmp(input, eof_str) != 1)
	{
		if (ft_strlen(input) > 0)
			write(output, input, ft_strlen(input));
		write(output, "\n", 1);
		ft_free(input);
		input = readline("> ");
	}
	ft_free(input);
	ft_free(eof_str);
	ft_free(filename);
	close(output);
	return (0);
}

static void	check_heredoc_call(t_cenas *cenas)
{
	t_list	*head;
	char	*eof;
	char	*i;

	eof = NULL;
	if (cenas->in.heredoc)
		head = cenas->in.heredoc;
	while (cenas->in.heredoc)
	{
		eof = (char *)cenas->in.heredoc->content;
		if (create_hrdoc_file(ft_substr(eof, 2, ft_strlen(eof)), eof) < 0)
			printf("Error: unable to create heredoc file\n");
		cenas->in.heredoc = cenas->in.heredoc->next;
	}
	if (eof)
		cenas->in.heredoc = head;
}

static int	check_loop(t_tree *t)
{
	t_cenas		*cenas;
	static int	step;

	cenas = (t_cenas *)t->content;
	if (!cenas)
		return (0);
	check_heredoc_call(cenas);
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
		ret = check_loop(t->leafs[i]);
		if (ret == 0 && t->leafs[i])
			check_heredoc(t->leafs[i]);
	}
}
