/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 06:59:15 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 07:29:29 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(void)
{
	if (chdir(g_global.argv[1]) != 0)
	{
		if (errno == ENOENT)
			printf("cd: no such file or directory: %s", g_global.argv[1]);
		printf("Failed to execute command \"%s\"\n", g_global.argv[0]);
	}
}
