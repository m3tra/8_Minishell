/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:02:25 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 04:30:52 by fporto           ###   ########.fr       */
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

# define INPUT_LEN 1000
# define PROMPT " Gui:>"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

// typedef struct s_input
// {
// 	char		*input;
// }				t_input;

typedef struct s_export
{
	char	*key;
	char	*value;
}	t_export;

typedef struct s_global
{
	struct s_env	*env;
	// struct s_input	*input;
	char			*input;
	char			*cwd;
	char			**argv;
	t_list			*exports;
}					t_global;

char	**split_args(char const *s);
t_env	*parseenv(char **env, int a);
void	free_global();

void	builtin(char **argv);

extern t_global	g_global;

#endif
