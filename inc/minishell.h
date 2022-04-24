#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "readline.h"
# include "history.h"

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char			*env_name;
	char			*env_value;
	struct s_env	*next;
}					t_env;

typedef struct s_input
{
	char		*input;
}				t_input;

char	**split_args(char const *s, char c);

#endif
