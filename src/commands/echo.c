/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:02:27 by fporto            #+#    #+#             */
/*   Updated: 2022/11/28 01:24:27 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_simple_cmd *sCmd)
{
	int		n_flag;
	char	*echo;
	size_t	i;

	n_flag = 0;
	i = 0;
	if (!ft_strcmp(sCmd->args[1], "-n"))
	{
		n_flag = 1;
		i += 1;
	}
	if (sCmd->heredoc)
		return ;
	echo = ft_strdup(sCmd->args[i + 1]);
	if (!echo)
		exit(EXIT_FAILURE);
	printf("%s", echo);
	if (!n_flag)
		printf("\n");
	free(echo);
}
