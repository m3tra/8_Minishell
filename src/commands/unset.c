/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:02:38 by fporto            #+#    #+#             */
/*   Updated: 2022/06/16 17:44:25 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char *var)
{
	t_export	*iter;
	char		*key;
	t_export	*rm;

	iter = g_global.exports;
	if (iter->next)
		key = iter->next->key;
	while (iter->next && ft_strcmp(key, var))
	{
		key = iter->next->key;
		iter = iter->next;
	}
	rm = iter->next;
	if (iter->next->next)
		iter->next = iter->next->next;
	else
		iter->next = NULL;
	free(rm->key);
	free(rm->value);
}
