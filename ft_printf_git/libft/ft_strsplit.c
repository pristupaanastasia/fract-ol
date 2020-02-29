/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 21:33:19 by smanhack          #+#    #+#             */
/*   Updated: 2019/08/28 15:49:44 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_number_words_1(char const *s, char c)
{
	size_t count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static size_t	ft_number_letters(char const *s, char c)
{
	size_t count;

	count = 0;
	while (*s && *s != c)
	{
		s++;
		count++;
	}
	return (count);
}

static char		**ft_fill_word(char const **s, char c, char **p, size_t i)
{
	size_t	j;

	p[i] = ft_strnew(ft_number_letters(*s, c));
	if (!p[i])
		return (NULL);
	j = 0;
	while (**s && **s != c)
	{
		p[i][j] = **s;
		(*s)++;
		j++;
	}
	return (p);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**p;
	size_t	i;
	size_t	n_w;

	if (!s)
		return (NULL);
	n_w = ft_number_words_1(s, c);
	p = (char **)malloc(sizeof(*p) * (n_w + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (n_w)
		{
			p = ft_fill_word(&s, c, p, i);
			if (!p[i++])
				return (ft_freesplit(p, i));
			n_w--;
		}
	}
	p[i] = NULL;
	return (p);
}
