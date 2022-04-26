/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/04/26 02:12:30 by fporto           ###   ########.fr       */
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

// static void	check_asp(char	**argv)
// {
// 	int len;
// 	int a;
// 	int b;

// 	(void) argv;
// 	a = 0;
// 	while(argv[++a])
// 	{
// 		b = -1;
// 		while(argv[a][++b])
// 		{
// 			if (argv[a][b] != '\\')
// 				b += 2;
// 			else if (argv[a][b] == 34)
// 			{
// 				len = ft_strchr(&argv[a][b + 1], 34) - &argv[a][b + 1];
// 				if (!ft_strchr(&argv[a][b + 1], '&'))
// 					b += len;
// 			}
// 			else if (argv[a][b] == 39)
// 				b += (ft_strchr(&argv[a][b + 1], 34) - &argv[a][b]);
// 		}
// 	}
// }
// static void	check_meta(char	**argv)
// {
// 		if (argv[a][b] == '>')
// 		{
// 			if (argv[a][b + 1] == '>')
// 			{
// 				//append outgoing redirection
// 			}
// 			else{}
// 				//outgoing redirection
// 		}
// 		if (argv[a][b] == '<')
// 		{
// 			//input redirection
// 			if (argv[a][b + 1] == '<')
// 				b++;
// 		}
// 		if (argv[a][b] == '*')
// 		{
// 			//file substitution wildcard;zero or more characters
// 		}
// 		if (argv[a][b] == '?')
// 		{
// 			//File substitution wildcard; one character
// 		}
// 		if (argv[a][b] == '[' && argv[a][b + 1] == ']')
// 		{
// 			if (ft_strchr(argv[a], ']')){}
// 				//File substitution wildcard; any character between brackets
// 		}
// 		if (argv[a][b] == '`')
// 		{
// 			if (!ft_strcmp(&argv[a][b], "`cmd`")){}
// 		}
// 		if (argv[a][b] == '$')
// 		{
// 			if (!ft_strcmp(&argv[a][b], "$(cmd)")){}
// 			else if (argv[a][b + 1] == '$'){}
// 			else{}
// 		}
// 		if (argv[a][b] == '|')
// 		{
// 			if(argv[a][b + 1] == '|'){}
// 				// OR
// 			else{}
// 				//pipe
// 		}
// 		if (argv[a][b] == ';')
// 		{
// 			//Command sequence, Sequences of Commands
// 		}
// 		if (argv[a][b] == '(' && argv[a][b + 1] == ')')
// 		{
// 			//Group commands, Sequences of Commands
// 		}
// 		if (argv[a][b] == '&')
// 		{
// 			if (argv[a][b + 1] == '&'){}
// 				// AND
// 			else{}
// 				//Run command in the background, Background Processes
// 		}
// 		if (argv[a][b] == '#')
// 		{
// 			// Comment
// 		}
// }

static void	read_command(void)
{
	char	*prompt;
	char	*last;
	char	*tmp;

	ft_free(g_global.cwd);
	g_global.cwd = getcwd(NULL, INPUT_LEN);
	prompt = ft_strdup(PROMPT);
	last = last_dir();
	tmp = ft_strjoin(last, prompt);
	free(last);
	free(prompt);
	g_global.input = readline(tmp);
	while (!g_global.input)
		g_global.input = readline(tmp);
	free(tmp);
	if (*g_global.input)
		add_history(g_global.input);
	free_arr(g_global.argv);
	g_global.argv = split_args(g_global.input);
	// check_asp(g_global.argv);
}

static void	sigint_action(int signal)
{
	rl_replace_line("", signal);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	pid_t	pid;

	global_init(env);

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_action);

	while (1)
	{
		read_command();
		if (!ft_strcmp(g_global.argv[0], "cd"))
			cd();
		else if (!ft_strcmp(g_global.argv[0], "exit"))
			break ;
		pid = fork();
		if (!pid)
		{
			builtin();
			not_builtin();
		}
		else
		{
			wait(NULL);

		}
	}
	free_global(NULL);
}
