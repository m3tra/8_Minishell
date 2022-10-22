/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:03:59 by fheaton-          #+#    #+#             */
/*   Updated: 2022/10/22 17:36:19 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

# define DEL = 131
# define B = 130
# define DQ = 129
# define D = 128

typedef struct s_cmd
{
	char	*line;
	char	**cmd;
	char	cmd_flags;
	t_inout	in;
}				t_cmd;

typedef struct s_inout
{
	t_list	*in;
	t_list	*input;
	t_list	*heredoc;
	t_list	*out;
	t_list	*output;
	t_list	*append;
}				t_inout;

typedef struct s_commands
{
	char	*line;
	t_tree	*tree;
}				t_commands;

typedef struct s_tree
{
	void			*content;
	int				lcount;
	struct s_tree	**leafs;
}				t_tree;

t_tree	*treenew(void *content);
int		treeadd(t_tree *tree, void *content);
int		treeclear(t_tree *t, void (*del)(void *));
void	*realloc(void *ptr, size_t osize, size_t nsize);

#endif
