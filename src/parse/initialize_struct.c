/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:57 by fheaton-          #+#    #+#             */
/*   Updated: 2022/10/30 15:13:56 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd	*initialize_struct(t_commands *cmd)
{
	t_cmd	*cenas;

	cenas = calloc(1, sizeof(t_cmd));
	if (!cenas)
		return (NULL);
	cenas->currSimpleCmd = initialize_Simple(cmd);
	cenas->currCmd = cenas;
}
