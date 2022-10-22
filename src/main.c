/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:29:25 by fporto            #+#    #+#             */
/*   Updated: 2022/10/22 18:13:04 by fheaton-         ###   ########.fr       */
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

t_commands	*parse(char	*input)
{
	t_commands *cmd;
	int err;

	err = 0;
	cmd = check_input(input);
	if (!cmd)
		return (NULL);
	cmd->tree = treenew(NULL);
	cmd->line = parse_q(ft_strdup(input), 0, cmd);
	if ((split_cmd(cmd->tree, cmd->line, 0) - 1) == (int)ft_strlen(cmd->line))
		return (NULL);
	if (!parse_out(cmd->tree))
		return (NULL);
	if (!expand(cmd->tree))
		return (NULL);
	if (!word_split(cmd->tree))
		err = 1;
	if (!err)
		unmask(cmd->tree);
	return (cmd);
	
}

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
		if (!(parse(g_global.input)))
		{
			bad input;
			continue ;
		}
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
