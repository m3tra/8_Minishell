/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 07:26:49 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

static char	*last_dir(void)
{
	size_t	len;

	len = ft_strlen(g_global.cwd);
	while (len > 0 && g_global.cwd[len - 1] != '/')
		len--;
	return (ft_strdup(g_global.cwd + len));
}

void	read_command(void)
{
	char	*prompt;
	char	*last;
	char	*tmp;

	g_global.cwd = getcwd(NULL, INPUT_LEN);
	prompt = ft_strdup(PROMPT);
	last = last_dir();
	tmp = ft_strjoin(last, prompt);
	free(last);
	free(prompt);
	g_global.input = readline(tmp);
	while (!g_global.input)
		readline(tmp);

	g_global.argv = split_args(g_global.input);

	builtin(g_global.argv);

	free(tmp);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	global_init(env);

	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, );

	while (1)
	{
		read_command();
	}
	free_global();
}
