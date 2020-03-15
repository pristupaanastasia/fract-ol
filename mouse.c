/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:30:16 by mriley            #+#    #+#             */
/*   Updated: 2020/03/10 18:30:20 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_press(int keykode, t_mlx_point *param)
{
	if (keykode == 53)
		exit(0);
	else if (keykode == 69)
		param->zoom *= 0.99;
	else if (keykode == 78)
		param->zoom /= 0.99;
	else if (keykode == 124)
		param->offset_x -= (param->zoom * 0.05);
	else if (keykode == 123)
		param->offset_x += (param->zoom * 0.05);
	else if (keykode == 126)
		param->offset_y -= (param->zoom * 0.05);
	else if (keykode == 125)
		param->offset_y += (param->zoom * 0.05);
	param->x_zoom = (WIN_HEIGHT / 4) * (param->zoom * 0.0001);
	param->y_zoom = (WIN_WIDTH / 4) * (param->zoom * 0.0001);
	if (param->num == 2)
		julia(param->x, param->y, &param);
	if (param->num != 2)
		draw_fractal(&param);
	return (0);
}

int		mouse_move(int x, int y, t_mlx_point *param)
{
	param->x = x;
	param->y = WIN_HEIGHT - y;
	if (param->num == 2)
		julia(param->x, param->y, &param);
	return (0);
}

void	init_draw(t_mlx_point *new)
{
	new->max_it = 50;
	new->min = init_complex(-2.0, -2.0);
	new->max.re = 2.0;
	new->max.im = new->min.im + (new->max.re - new->min.re) * WIN_HEIGHT /
	WIN_WIDTH;
	new->factor = init_complex((new->max.re - new->min.re) / (WIN_WIDTH - 1),
	(new->max.im - new->min.im) / (WIN_HEIGHT - 1));
	new->mouse = init_complex((double)new->x_zoom / (WIN_WIDTH / new->max.re
	- new->min.re) + new->min.re, (double)new->y_zoom / (WIN_HEIGHT /
	new->max.im - new->min.im) * -1 + new->max.im);
	new->min.re = interpolate(new->mouse.re, new->min.re, 1.0 / new->zoom);
	new->min.im = interpolate(new->mouse.im, new->min.im, 1.0 / new->zoom);
	new->max.re = interpolate(new->mouse.re, new->max.re, 1.0 / new->zoom);
	new->max.im = interpolate(new->mouse.im, new->max.im, 1.0 / new->zoom);
	new->y_k = new->start - 1;
	new->x_k = 0;
}

void	free_mass(t_mnim *mnim1, int *mas1)
{
	free(mnim1);
	free(mas1);
}
