/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:02:27 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 07:06:02 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(void)
{
	char	*echo;
	size_t	i;

	i = 0;
	while (g_global.input[i] && g_global.input[i] != ' ')
		i++;
	echo = ft_strdup(g_global.input + i + 1);
	if (!echo)
		exit(EXIT_FAILURE);
	printf("%s\n", echo);
	free(echo);
}
