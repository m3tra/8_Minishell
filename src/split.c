/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:02:34 by fporto            #+#    #+#             */
/*   Updated: 2022/04/25 07:17:25 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_spacer(char c)
{
	return ((c == ' ') || (c == '|') || (c == '&') || (c == '<') || (c == '>'));
}

static size_t	nb_words(char *s)
{
	size_t	i;
	size_t	nb;
	int		s_quote;
	int		dbl_quote;

	s_quote = 0;
	dbl_quote = 0;
	if (!s)
		return (0);
	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && is_spacer(s[i]))
			i++;
		if (!s[i])
			return (nb);
		while (s[i] && !is_spacer(s[i]))
			i++;
		nb++;
		while (s[i] && is_spacer(s[i]))
			i++;
	}
	return (nb);
}

static int	spaces(char *s)
{
	size_t	i;

	i = 0;
	while (is_spacer(s[i]))
		i++;
	return (i);
}

static char	*get_word(char *s)
{
	char	*word;
	size_t	i;

	i = 0;
	if (!s[i])
		return (0);
	while (*s && is_spacer(*s))
		s++;
	while (s[i] && !is_spacer(s[i]))
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && !is_spacer(s[i]))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**split_args(char const *s)
{
	char	**arr;
	char	*str;
	size_t	i;
	size_t	start;
	size_t	nb;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	nb = nb_words((char *)str);
	arr = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!arr)
		return (NULL);
	if (!nb)
		return (NULL);
	i = -1;
	start = spaces(str);
	while (++i < nb)
	{
		arr[i] = get_word(str + start);
		start += (ft_strlen(arr[i]));
		start += spaces(str + start);
	}
	return (arr);
}
