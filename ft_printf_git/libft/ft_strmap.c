/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:23:14 by smanhack          #+#    #+#             */
/*   Updated: 2019/04/07 14:24:13 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*p;
	unsigned int	i;

	if (s && f)
	{
		p = (char *)malloc(sizeof(*p) * (ft_strlen(s) + 1));
		if (p)
		{
			i = 0;
			while (s[i] != '\0')
			{
				p[i] = (*f)(s[i]);
				i++;
			}
			p[i] = '\0';
			return (p);
		}
	}
	return (NULL);
}
