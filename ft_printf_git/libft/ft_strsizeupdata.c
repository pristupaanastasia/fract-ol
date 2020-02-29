/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsizeupdata.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:47:14 by noobythetur       #+#    #+#             */
/*   Updated: 2019/05/23 15:47:11 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsizeupdata(char *src, size_t size, size_t add_size)
{
	char	*res;

	res = ft_strnew(size + add_size);
	if (src && res)
	{
		ft_strncpy(res, src, size);
		if (add_size > 0)
			ft_bzero(res + size, add_size);
		ft_strdel(&src);
		res[size + add_size + 1] = '\0';
	}
	return (res);
}
