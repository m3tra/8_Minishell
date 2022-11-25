/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:58:32 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/25 16:35:54 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	*ft_realloc(void *ptr, size_t osize, size_t nsize)
{
	char	*ret;

	if (!ptr)
		return (malloc(nsize));
	if (!nsize)
		free(ptr);
	if (!nsize)
		return (NULL);
	ret = ft_calloc(nsize, 1);
	if (!ret)
		return (ptr);
	if (osize > nsize)
		osize = nsize;
	ft_memcpy(ret, ptr, osize);
	free(ptr);
	return (ret);
}

t_tree	*treenew(void *content)
{
	t_tree	*ret;

	ret = ft_calloc(1, sizeof(t_tree));
	if (!ret)
		return (NULL);
	ret->content = content;
	return (ret);
}

int	treeadd(t_tree *tree, void *content)
{
	t_tree	*new;

	new = treenew(content);
	if (!new)
		return (0);
	tree->leafs = ft_realloc(tree->leafs, tree->lcount * sizeof(t_tree),
			(tree->lcount + 1) * sizeof(t_tree));
	tree->leafs[tree->lcount++] = new;
	return (1);
}

int	treeclear(t_tree *t, void (*del)(void *))
{
	if (!t)
		return (0);
	del(t->content);
	while (t->lcount)
		treeclear(t->leafs[--t->lcount], del);
	free(t->leafs);
	free(t);
	return (1);
}
