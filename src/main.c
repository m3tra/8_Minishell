/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/07/25 23:23:33 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

// static char	*last_dir(void)
// {
// 	size_t	len;

// 	len = ft_strlen(g_global.cwd);
// 	while (len > 0 && g_global.cwd[len - 1] != '/')
// 		len--;
// 	return (ft_strdup(g_global.cwd + len));
// }

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

static void	read_command(void)
{
	char	*tmp;printf(CLR_BLUE"[%s]\n"CLR_RST, g_global.cwd);
	tmp = ft_strdup(PROMPT);
	while ("drip")
	{
		g_global.input = readline(tmp);
		if (g_global.input && ft_strlen(g_global.input) != 0)
			break;
		else if (g_global.input)
			free(g_global.input);
		if (!g_global.input || g_global.exit)
		{
			free(tmp);
			free_global(NULL);
		}
	}
	free(tmp);
	if (*g_global.input)
		add_history(g_global.input);
	free_arr(g_global.argv);
	g_global.argv = split_args(g_global.input);
	check_meta(g_global.argv);
}

void	handle_io(void)
{
	char	*fileIn;
	char	*fileOut;

	// Save STDIN/STDOUT
	int		originalFdIn = dup(STDIN_FILENO);
	int		originalFdOut = dup(STDOUT_FILENO);

	// Set the initial input
	int		fdIn;
	// If there is a specified input file ( < *.* ) open it
	// Else use default input
	if (fileIn)
		fdIn = open(fileIn, O_RDONLY);
	else
		fdIn = dup(originalFdIn);

	int		ret;
	int		fdOut;

	int		nSimpleCommands;
	t_simple_cmd	**simpleCmds;

	nSimpleCommands = g_global.fullCmd.nSimpleCmds;
	simpleCmds = g_global.fullCmd.simpleCmds;
	for (int i = 0; i < nSimpleCommands; i++)
	{
		//redirect input
		dup2(fdIn, STDIN_FILENO);
		close(fdIn);
		//setup output
		if (i == nSimpleCommands - 1)
		{
			// Last simple command
			// If there is a specified output file ( > *.* ) open it
			// Else use default output
			if (fileOut)
				fdOut = open(fileOut, O_RDWR | O_CREAT, 0777);
			else
				fdOut = dup(originalFdOut);
		}
		else
		{
			// Not last simple command
			//create pipe
			int fdPipe[2];
			pipe(fdPipe);
			fdOut = fdPipe[1];
			fdIn = fdPipe[0];
		}// if/else
		// Redirect output
		dup2(fdOut, STDOUT_FILENO);
		close(fdOut);

		if (is_builtin(simpleCmds[i]->args[0]))
			builtin(simpleCmds[i]->args[0]);
		else
		{
			ret = not_builtin(simpleCmds[i]->args[0]);
			if (!ret)
				free_global(CLR_RED"Command not found"CLR_RST);
		}
		// // Create child process
		// ret = fork();
		// if (ret == 0) {
		// 	execvp(scmd[i].args[0], scmd[i].args);
		// 	perror("execvp");
		// 	_exit(1);
		// }
	} //  for
	//restore in/out defaults
	dup2(originalFdIn, STDIN_FILENO);
	dup2(originalFdOut, STDOUT_FILENO);
	close(originalFdIn);
	close(originalFdOut);
	// Wait for last command
	if (ret && !g_global.background)
		waitpid(ret, NULL, NULL);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*cmd;

	global_init(env);
	signal(SIGQUIT, SIG_IGN);		// Ctrl + \		//
	signal(SIGINT, sigint_action);	// Ctrl + C
	while ("swag")
	{
		read_command();
		cmd = g_global.argv[0];
		if (!ft_strcmp(cmd, "cd")){
			cd();
			continue;
		}
		else if (!ft_strcmp(cmd, "exit"))
			break ;
		if (!builtin(cmd))
			not_builtin(cmd);
		// printf("test\n");
		wait(NULL);
	}
	free_global(NULL);
}
