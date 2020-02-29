/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:41:10 by mriley            #+#    #+#             */
/*   Updated: 2019/08/28 15:17:04 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"
#include <limits.h>

char		*izdvatodestocd(double n, t_format f)
{
	int		i;
	char	*h;
	int		p;

	i = 0;
	p = 6;
	if (f.prec > 0)
		p = f.prec;
	if (f.prec == 0)
		p = 1;
	if (n < 0.0)
		n = -n;
	h = (char*)malloc(p + 2);
	while (i < p)
	{
		n = n * 10;
		h[i++] = (int)n + '0';
		n = n - (int)n;
	}
	h[i] = '\0';
	if (h[0] >= '5' && f.prec == 0)
		return (ft_strdup("1.0"));
	if ((h[i - 1] - 48) % 2 != 0)
		h = ft_okruglyaem(h, n * 10);
	return (h);
}

void		toretryd_part_2(t_point *p, long long *i, t_format *ff)
{
	p->znak = ft_znakd(p->s);
	p->exp = ft_expd(p->s);
	p->mantissa = ft_mantissad(p->s);
	*i = izdestodvad(p->exp);
	p->mantissa = dvigaemd(*i, p->mantissa);
	p->g = todesd(p->mantissa);
	p->posle = dlinayadrob(p->mantissa, *ff);
}

void		ft_free(t_point p)
{
	free(p.mantissa);
	free(p.g);
	free(p.s);
	free(p.exp);
	free(p.zifra);
	free(p.toc);
}

void		ft_toretryd_bonus(t_point *p, char **stroka, t_format *ff)
{
	if (p->toc[1] == '.' && proverka(p->toc, p->zifra) != 1)
	{
		p->zifra = ft_peredelzel(p->zifra, ft_strlen(p->zifra));
		p->toc = tocotrub(p->toc);
	}
	if (ff->prec != 0)
	{
		*stroka = ft_strjoin(p->zifra, ".");
		free(p->zifra);
		p->zifra = *stroka;
		*stroka = ft_strjoin(p->zifra, p->toc);
		ft_free(*p);
		p->zifra = *stroka;
	}
}

char		*toretryd(va_list ap, t_format ff)
{
	double		n;
	long long	i;
	t_point		p;
	char		*stroka;

	if (ff.prec == 0)
		ff.prec = 6;
	if (ff.prec == -1)
		ff.prec = 0;
	if (ff.type == 2)
		return (toretry(ap, ff));
	n = va_arg(ap, double);
	p.s = ft_putbitd(&n, 8);
	toretryd_part_2(&p, &i, &ff);
	p.zifra = ft_delaem(p.g, p.znak, p.mantissa);
	p.toc = todestocd(n, ff);
	ft_toretryd_bonus(&p, &stroka, &ff);
	return (p.zifra);
}
