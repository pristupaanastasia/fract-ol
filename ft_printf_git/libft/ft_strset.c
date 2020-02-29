/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:45:16 by smanhack          #+#    #+#             */
/*   Updated: 2019/05/23 15:28:24 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strset(char *b, char c, size_t len)
{
	char *p;

	p = b;
	while (len--)
	{
		*p = c;
		p++;
	}
	return (b);
}
