/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:02:25 by fporto            #+#    #+#             */
/*   Updated: 2022/11/27 18:22:43 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "readline.h"
# include "history.h"
# include "parse.h"

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

# define CLR_RED	"\033[38;5;1m"
# define CLR_GREEN	"\033[38;5;47m"
# define CLR_BLUE	"\033[0;34m"
# define CLR_CYAN	"\033[38;5;14m"
# define CLR_YELLOW	"\033[33m"
# define CLR_PURPLE	"\033[38;5;13m"
# define CLR_WHITE	"\033[0;37m"
# define CLR_BLACK	"\033[0;30m"
# define CLR_RST	"\033[0m"

# define INPUT_LEN	1000
# define PROMPT		"\033[38;5;13mGuiSH:> \033[0m"

// // // Describes a simple command and arguments
// typedef struct	s_simple_cmd
// {
// 	// Available space for arguments currently preallocated
// 	int		nAvailableArgs;
// 	// Number of arguments
// 	int		nArgs;
// 	// Array of arguments
// 	char	**args;

// }	t_simple_cmd;

// // // Describes a complete command with the multiple pipes if any
// // // and input/output redirection if any.

// typedef struct s_cmd
// {
// 	int					_nAvailableSimpleCmds;
// 	int					n_simple_cmds;
// 	t_simple_cmd		**simpleCmds;
// 	char				*_out_file;
// 	char				*_input_file;
// 	char				*_err_file;
// 	int					_background;
// 	struct t_full_cmd	*currCmd;
// 	t_simple_cmd		*currSimpleCmd;
// }				t_full_cmd;

typedef struct s_simple_cmd t_simple_cmd;
typedef struct s_full_cmd t_full_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;
}	t_export;

typedef struct s_global
{
	t_env		*env_list;
	char		**env;
	char		**argv;
	char		*path;
	char		**path_dirs;
	char		*cwd;
	t_full_cmd	*full_cmd;
	char		*input;
	char		*infile;
	char		*outfile;
	char		*errfile;
	int			exit;
	int			background;
	t_export	*exports;
}	t_global;

extern t_global	g_global;

char	**split_args(char const *s);

void	update_cwd(void);

void	global_init(char **env);
void	free_arr(char **arr);
void	free_global(char *err);

void	free_env(t_env *env_vars);
t_env	*parse_env(char **env, int a);

void	parse_path(void);

void	cd(void);
void	echo(void);
void	export(void);
void	unset(char *var);

int		is_builtin(char *cmd);
int		builtin(t_simple_cmd *sCmd);
// int	builtin(char *cmd);
pid_t	not_builtin(t_simple_cmd *sCmd);
pid_t	execute(char *path);

// testingFuncs
void	print_str_array(char **arr);

#endif
