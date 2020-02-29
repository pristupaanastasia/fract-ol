/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:25:37 by smanhack          #+#    #+#             */
/*   Updated: 2019/04/05 17:25:40 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t ld;
	size_t ls;

	ls = ft_strlen(src);
	ld = ft_strlen(dst);
	i = 0;
	while (i < ls && i + ld + 1 < size)
	{
		dst[i + ld] = src[i];
		i++;
	}
	dst[i + ld] = '\0';
	if (size < ld)
		ld = size;
	return (ld + ls);
}
