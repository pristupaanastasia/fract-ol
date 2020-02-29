/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:53:09 by smanhack          #+#    #+#             */
/*   Updated: 2019/04/07 17:53:11 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int fl;

	fl = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		fl = -1;
	}
	if (n / 10)
		ft_putnbr_fd(n / 10 * fl, fd);
	ft_putchar_fd(n % 10 * fl + 48, fd);
}
