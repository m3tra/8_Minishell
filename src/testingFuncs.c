/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testingFuncs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:44:39 by fporto            #+#    #+#             */
/*   Updated: 2022/11/25 20:48:46 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_str_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		printf("\t%s\n", arr[i++]);
}

void	print_cenas(t_cenas *cenas) {
	// char *line
	if (!cenas) {
		printf("cenas: NULL\n");
		return ;
	}

	char	*line = cenas->line;
	if (line)
		printf("line(%ld): %s\n", ft_strlen(line), line);
	else
		printf("line: NULL\n");

	// char **cmd

	char	**cmd;
	cmd = cenas->cmd;
	int		i;
	i = -1;
	while (cmd[++i])
		printf("cmd[%d](%ld): %s\n", i, ft_strlen(cmd[i]), cmd[i]);

	// t_flags *cmd_flags

	// t_flags	*flags;
	// flags = cenas->cmd_flags;
	// if (flags->question)
	// 	printf("question: %d\n", flags->question);
	// if (flags->and)
	// 	printf("and: %d\n", flags->and);
	// if (flags->or)
	// 	printf("or: %d\n", flags->or);
	// if (flags->end_list)
	// 	printf("end_list: %d\n", flags->end_list);
	// if (flags->res_logic)
	// 	printf("res_logic: %d\n", flags->res_logic);
	// if (flags->pipe)
	// 	printf("pipe: %d\n", flags->pipe);

	// t_inout in
}

// Recursively prints leaves
void	print_tree(t_tree *tree) {
	t_cenas		*cenas;
	int			lcount;
	static int	i;

	cenas = (t_cenas *)tree->content;
	lcount = tree->lcount;
	i = -1;

	if (!tree) {
		printf("tree: NULL\n");
		return ;
	}
	printf("================================================================\n");
	printf("\nleaf nr: %d with %d total leafs\n\n", i + 1, lcount);
	print_cenas(cenas);

	while (++i < lcount)
		print_tree(tree->leafs[i]);
	
}
