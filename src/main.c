/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/11/28 01:19:18 by fheaton-         ###   ########.fr       */
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

static int	is_input_only_spaces(void) {
	size_t	i;

	i = 0;
	while (i < ft_strlen(g_global.input) - 1)
		if (g_global.input[i++] != ' ')
			return (0);
	return (1);
}

static void	read_command(void)
{
	char	*tmp;
	printf(CLR_BLUE"[%s]\n"CLR_RST, g_global.cwd);
	tmp = ft_strdup(PROMPT);
	while ("drip")
	{
		g_global.input = readline(tmp);
		if (g_global.input && ft_strlen(g_global.input) != 0)
			break ;
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
}



// void	print_full_cmd(void) {
// 	int	n_simple_cmds = g_global.full_cmd->n_simple_cmds;
// 	int	n_args = 0;
// 	if (n_simple_cmds)
// 		n_args = g_global.full_cmd->simple_cmds[0]->n_args;
// 	printf("=================\n");
// 	printf("Full_cmd:\n");
// 	printf("n_simple_cmds: %d\n", n_simple_cmds);
// 	for (int i = 0; i < n_simple_cmds; i++) {
// 		printf("simple_cmds[%d]: \n", i);
// 		n_args = g_global.full_cmd->simple_cmds[i]->n_args;
// 		printf("n_args: %d\n", n_args);
// 		for (int j = 0; j < n_args; j++) {
// 			printf("arg[%d]: %s\n", j, g_global.full_cmd->simple_cmds[i]->args[j]);
// 		}
// 		if (g_global.full_cmd->simple_cmds[i]->args && \
// 				g_global.full_cmd->simple_cmds[i]->args[n_args] && \
// 				g_global.full_cmd->simple_cmds[i]->args[n_args] != NULL)
// 			printf("arg[%d]: Not NULL\n", n_args);
// 	}
// 	printf("=================\n\n");
// }

void	handle_io(void)
{
	// char	*fileIn;
	// char	*fileOut;

	// Save STDIN/STDOUT
	int		originalFdIn = dup(STDIN_FILENO);
	int		originalFdOut = dup(STDOUT_FILENO);

	// Set the initial input
	int		fdIn;
	// If there is a specified input file ( < *.* ) open it
	// Else use default input
	int		ret;
	int		fdOut;

	int		n_simple_cmds;
	t_simple_cmd	**simple_cmds;
	t_simple_cmd	*curr_simple_cmd;

	n_simple_cmds = g_global.full_cmd->n_simple_cmds;
	simple_cmds = g_global.full_cmd->simple_cmds;

	// print_full_cmd();

	for (int i = 0; i < n_simple_cmds; i++)
	{
		curr_simple_cmd = simple_cmds[i];

		if (curr_simple_cmd->_input_file)
			fdIn = open(curr_simple_cmd->_input_file, O_RDONLY);
		else
			fdIn = dup(originalFdIn);
		//redirect input
		dup2(fdIn, STDIN_FILENO);
		close(fdIn);
		//setup output
		if (i == n_simple_cmds - 1)
		{
			// Last simple command
			// If there is a specified output file ( > *.* ) open it
			// Else use default output
			if (curr_simple_cmd->_out_file) {
				// printf("_out_file: %s\n", curr_simple_cmd->_out_file);
				if (curr_simple_cmd->inout.append) {
					// printf("last append: %s\n", (char *)ft_lstlast(curr_simple_cmd->inout.append));
					fdOut = open((char *)ft_lstlast(curr_simple_cmd->inout.append)->content, O_RDWR | O_CREAT | O_APPEND, 0777);
				}
				else
					fdOut = open(curr_simple_cmd->_out_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			}
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

		if (is_builtin(curr_simple_cmd->args[0])) {
			// printf("test\n");
			builtin(curr_simple_cmd);
		}
		else
		{
			ret = not_builtin(curr_simple_cmd);
			if (!ret) {
				// free_global(CLR_RED"Command not found"CLR_RST);
				printf(CLR_RED"Command not found"CLR_RST);
				printf("\n");
			}
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
		waitpid(ret, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	// char			*cmd;

	t_simple_cmd *curr_simple_cmd;

	global_init(env);
	signal(SIGQUIT, SIG_IGN);		// Ctrl + \		//
	signal(SIGINT, sigint_action);	// Ctrl + C
	while ("swag")
	{
		update_cwd();
		read_command();
		if (is_input_only_spaces())
			continue ;
		// cmd = g_global.argv[0];
		// s_cmd->args[0] = cmd;
		g_global.full_cmd = parse(g_global.input);
		if (!g_global.full_cmd)
			continue ;
		curr_simple_cmd = g_global.full_cmd->curr_simple_cmd;
		if (!ft_strcmp(curr_simple_cmd->args[0], "cd")) {
			cd();
			continue ;
		}
		else if (!ft_strcmp(curr_simple_cmd->args[0], "exit"))
			break ;
		// if (!builtin(curr_simple_cmd))
		// 	not_builtin(curr_simple_cmd);
		handle_io();
		// curr_simple_cmd = ++*g_global.full_cmd->simple_cmds;
		wait(NULL);
	}
	free_global(NULL);
}
