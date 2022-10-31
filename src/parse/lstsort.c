/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:17:41 by fheaton-          #+#    #+#             */
/*   Updated: 2022/10/30 16:18:35 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	lstsort(t_list **l)
{
	t_list	*aux;
	void	*tmp;

	aux = *l;
	if (!aux)
		return ;
	while (aux->next)
	{
		if (ft_strncmp(aux->content, aux->next->content,
				ft_strlen(aux->content)) <= 0)
		{
			aux = aux->next;
			continue ;
		}
		tmp = aux->content;
		aux->content = aux->next->content;
		aux->next->content = tmp;
		aux = *l;
	}
}
