/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:29:23 by smanhack          #+#    #+#             */
/*   Updated: 2019/07/24 18:53:40 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *src, size_t size, size_t add_size)
{
	void	*res;

	res = ft_memalloc(size + add_size);
	if (src && res)
	{
		ft_memcpy(res, src, size);
		if (add_size > 0)
			ft_bzero(res + size, add_size);
		ft_memdel(&src);
	}
	return (res);
}
