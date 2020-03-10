/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:30:03 by mriley            #+#    #+#             */
/*   Updated: 2020/03/10 18:30:07 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_help(t_mlx_point *new)
{
	ft_bzero(new->mlx.img.data,
		WIN_WIDTH * WIN_HEIGHT * (new->mlx.img.bpp / 8));
	mlx_put_image_to_window(new->mlx.mlx_ptr, new->mlx.win,
		new->mlx.img.img_ptr, 0, 0);
	mlx_string_put(new->mlx.mlx_ptr, new->mlx.win, 295, 155, COLOR_SILVER,
		"Controls");
	mlx_string_put(new->mlx.mlx_ptr, new->mlx.win, 285, 200, COLOR_SILVER,
		"Move           - Arrows");
	mlx_string_put(new->mlx.mlx_ptr, new->mlx.win, 285, 230, COLOR_SILVER,
		"Zoom           - Scroll");
	mlx_string_put(new->mlx.mlx_ptr, new->mlx.win, 285, 260, COLOR_SILVER,
		"Julia Constant - Mouse");
	mlx_string_put(new->mlx.mlx_ptr, new->mlx.win, 285, 290, COLOR_SILVER,
		"Close Help     - Esc");
}

t_mnim		init_complex(double re, double im)
{
	t_mnim	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

double		interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

t_mnim		init_z(t_mlx_point *new, t_mnim z, t_mnim c, int *it)
{
	it[1]++;
	if (new->num == 2)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + new->k.re,
		2.0 * z.re * z.im + new->k.im);
	}
	if (new->num == 1)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + c.re,
		2.0 * z.re * z.im + c.im);
	}
	if (new->num == 3)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + c.re,
		-2.0 * fabs(z.re * z.im) + c.im);
	}
	return (z);
}

void		put_help(int arc, char **s, t_mlx_point *new)
{
	if ((arc == 2 && ft_strequ(s[1], "-help") == 1))
		draw_help(new);
	else
	{
		ft_printf("Use flags:\nburning ship\n");
		ft_printf("julia \nmandelbrot\nfor help '-help'\n");
		exit(0);
	}
}
