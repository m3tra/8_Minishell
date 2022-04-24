#include "libft.h"

static int	is_spacer(char c)
{
	return ((c == ' ') || (c == '|') || (c == '&') || (c == '<') || (c == '>'));
}

static size_t	nb_words(char *s)
{
	size_t	i;
	size_t	nb;

	if (s)
	{
		i = 0;
		nb = 0;
		while (s[i])
		{
			while (s[i] && is_spacer(s[i]))
				i++;
			if (!s[i])
				return (0);
			while (s[i] && !is_spacer(s[i]))
				i++;
			nb++;
			while (s[i] && is_spacer(s[i]))
				i++;
		}
		return (nb);
	}
	return (0);
}

static int	spaces(char *s)
{
	int	i;

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
	if (s[i])
	{
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
	return (0);
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
	arr[nb] = NULL;
	if (!nb)
		return (arr);
	i = -1;
	start = spaces(str);
	while (++i < nb)
	{
		arr[i] = get_word(s);
		start += (ft_strlen(arr[i]));
		start += spaces(str + start);
	}
	return (arr);
}
