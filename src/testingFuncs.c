#include "minishell.h"

void	print_str_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		printf("\t%s\n", arr[i++]);
}
