/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:10:13 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/20 00:59:15 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

// // Describes a simple command and arguments
typedef struct	s_simple_cmd
{
	// Available space for arguments currently preallocated
	int						nAvailableArgs;
	// Number of arguments
	int						nArgs;
	// Array of arguments
	char					**args;

	// mudar referencia da struct IMPORTANTE
	char					*_outFile;
	char					*_inputFile;
	char					*_errFile;
	int						append;
	int						heredoc;
}	t_simple_cmd;

// // Describes a complete command with the multiple pipes if any
// // and input/output redirection if any.

typedef struct s_cmd
{
	int				_nAvailableSimpleCmds;
	int				nSimpleCmds;
	t_simple_cmd	**simpleCmds;
	int				_background;
	t_simple_cmd	*currSimpleCmd;
}				t_cmd;

#endif
