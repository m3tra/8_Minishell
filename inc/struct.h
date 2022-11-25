/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:10:13 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/25 17:41:59 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

// Describes a simple command and arguments
typedef struct s_simple_cmd
{
	// Number of arguments
	int						n_args;
	// Array of arguments
	char					**args;

	// mudar referencia da struct IMPORTANTE
	char					*_out_file;
	char					*_input_file;
	char					*_err_file;
	int						append;
	int						heredoc;
	void					*next;
}	t_simple_cmd;

// Describes a complete command with the multiple pipes if any
// and input/output redirection if any.

typedef struct s_cmd
{
	int				n_simple_cmds;
	t_simple_cmd	**simple_cmds;
	int				_background;
	t_simple_cmd	*curr_simple_cmd;
}				t_full_cmd;

#endif
