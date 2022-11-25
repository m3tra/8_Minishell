/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:03:59 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/25 15:32:33 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "struct.h"

# define DEL -4
# define B -3
# define DQ -2
# define D -1

/**
 * flags: flags for each specific command (refer to cmd)
 *
 * question: at least one argument/cmd needs to expand exit code
 * and: cmd is to be executed before a &&.
 * or: cmd is to be executed before a ||.
 * end_list: cmd is at the end of a list.
 * res_logic: cmd is to be executed before a ; reseting the logic.
 * pipe: input piped to next command.
 */

typedef struct s_flags
{
	int	question;
	int	and;
	int	or;
	int	end_list;
	int	res_logic;
	int	pipe;
}				t_flags;

/**
 * in: pointer to the actual input node
 * input: Input for command if any. NULL for stdin otherwise contains path to
 *   file.
 * heredoc: Input for command if any.
 * 			If heredoc the string is specified here.
 * out: pointer to the actual output node
 * output: Output for command if any. NULL for stdout otherwise contains path to
 *   file.
 * append: Output for command to be appended if any.
 * 			If to append the string is specified here.
 */

typedef struct s_inout
{
	t_list	*in;
	t_list	*input;
	t_list	*heredoc;
	t_list	*out;
	t_list	*output;
	t_list	*append;
}				t_inout;

/**
 * cmd: command to be executed
 * cmd_flags: specific command's flags represented in a struct
 * 				with an int for each flag. int > 0 = a flag is active.
 * in: input
 */

typedef struct s_cenas
{
	char	*line;
	char	**cmd;
	t_flags	*cmd_flags;
	t_inout	in;
}				t_cenas;

typedef struct s_tree
{
	t_cenas			*cenas;
	int				lcount;
	struct s_tree	**leafs;
}				t_tree;

typedef struct s_commands
{
	char	*line;
	t_tree	*tree;
}				t_commands;

t_commands	*check_input(const char *str);
t_tree		*treenew(void *content);
int			treeadd(t_tree *tree, void *content);
int			treeclear(t_tree *t, void (*del)(void *));
void		*ft_realloc(void *ptr, size_t osize, size_t nsize);
char		*parse_q(char *str, int count);
int			split_cmd(t_tree *tree, char *line, int i);
int			parse_in_out(t_tree *tree);
int			expand(t_tree *t);
int			word_split(t_tree *t);
int			unmask(t_tree *t);
int			unmask_str(char *str);
t_cmd		*parse(char	*input);
t_cmd		*initialize_struct(t_commands *cmd);
int			ft_isspecial(char s);
void		lstsort(t_list **l);
int			wild(int i, char **s, t_cenas *cmd, int norm);

//testing funcs
void		print_tree(t_tree *tree);

#endif
