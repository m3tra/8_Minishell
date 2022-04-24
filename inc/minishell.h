#ifndef MINISHELL_H
# define MINISHELL_H

// # include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char			*env_n;
	char			*env_v;
	struct s_env	*next;
}				t_env;

#endif
