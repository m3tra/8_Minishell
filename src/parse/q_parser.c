/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:48:08 by fheaton-          #+#    #+#             */
/*   Updated: 2022/08/03 16:02:06 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unmask_str(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] >= 132);
			str[i] -= 132;
		if (str [i] == D)
			str[i] = '$';
	}
	return (1);
}

static char	*remove_q(char *str, int count)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(str) - count + 1, 1);
	i = -1;
	j = -1;
	while (str[++i])
		if (!ft_strchr("\\\"\'", str[i]))
			new[++j] = str[i];
	ft_free(str);
	return (new);
}

char	*parse_q(char *str, int count, t_commands *cmd)
{
	int		q;
	int		dq;
	int		skip;
	int 	in_var;
	char	*str2;

	q = 0;
	dq = 0;
	in_var = 0;
	str2 = str - 1;
	while(*++str2)
	{
		skip = 0;
		if (*str2 == '\'' && !dq)
		{
			q = !q;
			skip = !skip;
			count++;
		}
		if (*str2 == '\"' && !q)
		{
			dq = !dq;
			skip = !skip;
			count++;
		}
		if (*str2 == '$' && !q)
			in_var = 1;
		else if (ft_strchr(" \'\"\\;&|", *str2))
			in_var = 0;
		else if (*str2 == '$' && q)
			*str2 = 128;
		else if ((*str2 == '\\') && !q)
		{
			if (ft_strchar("\\\"$", *(str2 + 1)))
			{
				str2++;
				count++;
				if (*(str2 + 1) == '$')
					*str2 = D;
				else if (*(str2 + 1) == '\"')
					*str2 = DQ;
				else if (*(str2 + 1) == '\\')
					*str2 = B;
			}
		}
		else (*str2 < 128 && (q || dq) && !skip)
			*str2 += 132;
	}
	if (q || dq)
		return (NULL);
	return (remove_q(str, count));
}

