/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 07:03:01 by fporto            #+#    #+#             */
/*   Updated: 2022/04/27 19:30:32 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_add_back(t_export **lst, t_export *new)
{
	t_export	*list;
	t_export	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = *lst;
			while (tmp->next)
				tmp = tmp->next;
			list = tmp;
			list->next = new;
		}
	}
}

void	export(void)
{
	t_export	*export;
	int			key_len;
	int			value_len;
	int			i;

	export = malloc(sizeof(t_export));
	if (!export)
		exit(EXIT_FAILURE);
	key_len = 0;
	while (g_global.argv[1][key_len] && g_global.argv[1][key_len] != '=')
		key_len++;
	export->key = malloc(sizeof(char) * key_len + 1);
	i = -1;
	while (++i < key_len)
		export->key[i] = g_global.argv[1][i];
	export->key[i] = '\0';
	value_len = 0;
	while (g_global.argv[1][key_len + value_len + 1])
		value_len++;
	export->value = malloc(sizeof(char) * value_len + 1);
	i = -1;
	while (g_global.argv[1][key_len + ++i + 1])
		export->value[i] = g_global.argv[1][key_len + i + 1];
	export->value[value_len] = '\0';
	export_add_back(&g_global.exports, export);
}
