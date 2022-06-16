/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:02:25 by fporto            #+#    #+#             */
/*   Updated: 2022/06/16 17:03:41 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "readline.h"
# include "history.h"

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

# define INPUT_LEN 1000
# define PROMPT " Gui:>"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_export
{
	char				*key;
	char				*value;
	struct s_export		*next;
}	t_export;

typedef struct s_global
{
	t_env		*env_list;
	char		**envp;
	char		**path_dirs;
	char		*input;
	char		*cwd;
	char		**argv;
	t_export	*exports;
}	t_global;

extern t_global	g_global;

char	**split_args(char const *s);

void	global_init(char **env);
void	free_arr(char **arr);
void	free_global(char *err);

void	free_env(t_env *env_vars);
t_env	*parse_env(char **env, int a);

void	parse_path();

void	cd(void);
void	echo(void);
void	export(void);
void	unset(char *var);

void	builtin(void);

void	not_builtin(void);

#endif
