/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:15:52 by smanhack          #+#    #+#             */
/*   Updated: 2019/04/07 19:15:52 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*i_st;
	char	*i_en;
	size_t	len;
	char	*p;

	if (!s)
		return (NULL);
	while (*s && (*s == '\t' || *s == '\n' || *s == ' '))
		s++;
	i_st = (char *)s;
	i_en = i_st;
	while (*s)
	{
		if (*s != '\t' && *s != '\n' && *s != ' ')
			i_en = (char *)s;
		s++;
	}
	len = i_en - i_st + 1;
	p = ft_strnew(len);
	if (!p)
		return (NULL);
	while (len--)
		p[len] = i_st[len];
	return (p);
}
