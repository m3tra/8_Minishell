/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:02:38 by fporto            #+#    #+#             */
/*   Updated: 2022/04/27 19:34:09 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char *var)
{
	t_list		*iter;
	t_list		*tmp;
	t_export	*cont;
	t_export	*rm;

	iter = g_global.exports;
	if (iter->next)
		cont = (t_export *)iter->next->content;
	while (iter->next && ft_strcmp(cont->key, var))
	{
		cont = (t_export *)iter->next->content;
		iter = iter->next;
	}
	tmp = iter->next;
	rm = (t_export *)tmp->content;
	if (iter->next->next)
		iter->next = iter->next->next;
	else
		iter->next = NULL;
	free(rm->key);
	free(rm->value);
}
