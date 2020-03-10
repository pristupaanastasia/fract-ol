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
	{
		mlx_destroy_image(param->mlx.mlx_ptr, param->mlx.img.img_ptr);
		free(param);
		exit(0);
	}
	return (0);
}

int		mouse_press(int button, int x, int y, t_mlx_point *param)
{
	param->x_zoom = x;
	param->y_zoom = WIN_HEIGHT - y;
	if (button == 5 && param->num != 0)
	{
		if (param->zoom > 0.005 && param->zoom <= 0.05)
			param->zoom = param->zoom / 2;
		if (param->zoom > 0.05)
			param->zoom = param->zoom - 0.05;
		if (param->num == 2)
			julia(param->x, param->y, &param);
		if (param->num != 2)
			draw_fractal(&param);
	}
	if (button == 4 && param->num != 0)
	{
		param->zoom = param->zoom + 0.05;
		if (param->num == 2)
			julia(param->x, param->y, &param);
		if (param->num != 2)
			draw_fractal(&param);
	}
	return (0);
}

int		mouse_move(int x, int y, t_mlx_point *param)
{
	mlx_destroy_image(param->mlx.mlx_ptr, param->mlx.img.img_ptr);
	param->mlx.img.img_ptr = mlx_new_image(param->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT);
	param->mlx.img.data = (int *)mlx_get_data_addr(param->mlx.img.img_ptr,
	&(param->mlx.img.bpp), &(param->mlx.img.size_l), &(param->mlx.img.endian));
	param->x = x;
	param->y = WIN_HEIGHT - y;
	if (param->num == 2)
		julia(param->x, param->y, &param);
	return (0);
}

void	init_draw(t_mnim **mnim1, int **mas1, t_mlx_point *new)
{
	t_mnim	*mnim;
	int		*mas;

	mnim = *mnim1;
	mas = *mas1;
	mas[0] = 50;
	mnim[0] = init_complex(-2.0, -2.0);
	mnim[1].re = 2.0;
	mnim[1].im = mnim[0].im + (mnim[1].re - mnim[0].re) * WIN_HEIGHT /
	WIN_WIDTH;
	mnim[2] = init_complex((mnim[1].re - mnim[0].re) / (WIN_WIDTH - 1),
	(mnim[1].im - mnim[0].im) / (WIN_HEIGHT - 1));
	mnim[5] = init_complex((double)new->x_zoom / (WIN_WIDTH / mnim[1].re
	- mnim[0].re) + mnim[0].re, (double)new->y_zoom / (WIN_HEIGHT /
	mnim[1].im - mnim[0].im) * -1 + mnim[1].im);
	mnim[0].re = interpolate(mnim[5].re, mnim[0].re, 1.0 / new->zoom);
	mnim[0].im = interpolate(mnim[5].im, mnim[0].im, 1.0 / new->zoom);
	mnim[1].re = interpolate(mnim[5].re, mnim[1].re, 1.0 / new->zoom);
	mnim[1].im = interpolate(mnim[5].im, mnim[1].im, 1.0 / new->zoom);
	mas[2] = new->start;
	mas[3] = 0;
}

void	free_mass(t_mnim *mnim1, int *mas1)
{
	free(mnim1);
	free(mas1);
}
