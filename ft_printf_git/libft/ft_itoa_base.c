/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 20:15:56 by smanhack          #+#    #+#             */
/*   Updated: 2019/05/19 00:58:58 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int		ft_len(long nb, int base)
{
	int		k;

	k = 1;
	while ((nb /= base) != 0)
		k++;
	return (k);
}

static	int		ft_flag(long *value, int base)
{
	if (*value < 0)
	{
		if (base == 10)
			return (-1);
		else
			*value = (unsigned int)(*value);
	}
	return (1);
}

static	char	*ft_go(char *str, int k, long value, int base)
{
	int			sym;
	int			fl;

	fl = ft_flag(&value, base);
	while (k--)
	{
		if (fl == -1 && k == 0 && base == 10)
		{
			str[k] = '-';
			break ;
		}
		sym = value % base;
		if (sym >= 10 && sym <= 15)
			str[k] = 'a' + sym % 10;
		else
			str[k] = sym + 48;
		value /= base;
	}
	return (str);
}

char			*ft_itoa_base(long value, int base)
{
	int			fl;
	int			k;
	char		*str;

	fl = ft_flag(&value, base);
	k = ft_len(value, base);
	if (base < 2 || base > 16)
		return (NULL);
	if (base == 10 && fl == -1)
		k++;
	if ((str = (char*)malloc(sizeof(char) * (k + 1))) != NULL)
		str[k] = '\0';
	return (ft_go(str, k, value, base));
}
