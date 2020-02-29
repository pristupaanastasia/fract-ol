/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 13:28:06 by smanhack          #+#    #+#             */
/*   Updated: 2019/04/07 13:28:07 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!len && needle == NULL)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (len - j))
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
		len--;
	}
	return (NULL);
}
