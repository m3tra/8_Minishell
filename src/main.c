/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/06/17 18:52:00 by fporto           ###   ########.fr       */
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

char	*ft_strlchr(const char *s, int c, int len)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0' || len == 0)
	{
		if (s[i] == (unsigned char)c && s[i - 1] != '\\')
			return ((char *)s + i);
		i++;
		len--;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

int	handle_dollar(char *var)
{
	t_export *tmp;

	tmp = g_global.exports;
	while(strcmp(tmp->key, var))
		tmp = tmp->next;
	if (strcmp(tmp->key, var))
		return (1);
	return (0);
	//fazer alteração na string original
}

static void	check_meta(char	**argv)
{
	long 	len;
	int 	a;
	int 	b;
	char	*tmp;
	int		i;

	a = -1;
	while(argv[++a])
	{
		b = -1;
		while(argv[a][++b])
		{
			if (argv[a][b] == '\\')
				b += 2;
			else if (argv[a][b] == '\"')
			{
				len = (long)((unsigned long)ft_strchr(&argv[a][b + 1], '\"') - (unsigned long)&argv[a][b + 1]);
				tmp = ft_strlchr(&argv[a][b + 1], '$', len);
				if (tmp && tmp[-1] != '\\')
				{
					i = 0;
					while(ft_strchr(" \'\"\\;&|", tmp[i + 1]))
						i++;
					// if (handle_dollar(tmp, i))
					// 	//fazer alteração na string original
				}
				if (len > 0)
					b += (len + 1);
					// +1 para a aspa final
			}
			else if (argv[a][b] == '\'')
				b += (ft_strchr(&argv[a][b + 1], '\'') - &argv[a][b]) + 1;// +1 para a aspa final
			// else
			// 	// check_meta_extra(argv, a, b);
		}
	}
}

// static void	check_meta_extra(char	**argv, a, b)
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
// 		if (argv[a][b] == '|')
// 		{
// 			if(argv[a][b + 1] == '|'){}
// 				// OR
// 			else{}
// 				//pipe
// 		}
// 		if (argv[a][b] == '$')
// 		{
// 			//Expand the value of a variable
// 		}

//				//check implementation inside or outside "$"
// 						if (argv[a][b] == '?')
// 						{
// 							//File substitution wildcard; one character
// 						}

//				//bonus
// 						if (argv[a][b] == '&' && argv[a][b + 1] == '&')
// 						{
// 								// AND
// 						}
// 						if (argv[a][b] == '*')
// 						{
// 							//file substitution wildcard;zero or more characters
// 						}
// }    a || (b && c) && d

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
	while ("drip")
	{
		g_global.input = readline(tmp);
		if (g_global.input && ft_strlen(g_global.input) != 0)
			break;
		else if (g_global.input)
			free(g_global.input);
		if (!g_global.input || g_global.exit)
			free_global(NULL);
	}
	free(tmp);
	if (*g_global.input)
		add_history(g_global.input);
	free_arr(g_global.argv);
	g_global.argv = split_args(g_global.input);
	check_meta(g_global.argv);
}

/*
*	Ctrl+C handler
*/
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

	signal(SIGQUIT, SIG_IGN);		// Ctrl + \			//
	signal(SIGINT, sigint_action);	// Ctrl + C

	while ("swag")
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
