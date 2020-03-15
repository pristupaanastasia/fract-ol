/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:30:31 by mriley            #+#    #+#             */
/*   Updated: 2020/03/10 18:30:35 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_fractal_part(t_mlx_point *new)
{
	init_draw(new);
	while (++new->y_k < new->end)
	{
		new->c.im = ((new->max.im - new->y_k * new->factor.im) * new->zoom +
		new->y_zoom + new->offset_y);
		new->x_k = 0;
		while (new->x_k < WIN_WIDTH)
		{
			new->c.re = ((new->min.re + new->x_k * new->factor.re) * new->zoom +
			new->x_zoom + new->offset_x);
			new->z = init_complex(new->c.re, new->c.im);
			new->it = 0;
			while (pow(new->z.re, 2.0) +
			pow(new->z.im, 2.0) <= 4 && new->it < new->max_it)
			{
				new->z = init_z(new, new->z, new->c);
				new->it++;
			}
			new->mlx.img.data[new->y_k * (WIN_HEIGHT) +
			new->x_k++] = color_fractol(new->it, new->max_it);
		}
	}
}

void		draw_fractal(t_mlx_point **new1)
{
	pthread_t	threads[10];
	t_mlx_point	fractols[10];
	t_mlx_point	*new;
	int			i;

	new = *new1;
	i = 0;
	while (i < 10)
	{
		fractols[i] = *new;
		fractols[i].start = i * (WIN_HEIGHT / 10);
		fractols[i].end = (i + 1) * (WIN_HEIGHT / 10);
		pthread_create(&threads[i], NULL,
		(void *(*)(void *))draw_fractal_part, (void *)&fractols[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(new->mlx.mlx_ptr, new->mlx.win,
	new->mlx.img.img_ptr, 0, 0);
}

void		julia(int x, int y, t_mlx_point **new1)
{
	t_mlx_point	*new;

	new = *new1;
	ft_bzero(new->mlx.img.data, sizeof(sizeof(new->mlx.img.data)));
	new->k = init_complex(
		((double)x / WIN_WIDTH - 0.5),
		((double)y / WIN_HEIGHT - 0.5));
	draw_fractal(new1);
}

t_mlx_point	*init_new(void)
{
	t_mlx_point	*new;

	if ((new = (t_mlx_point*)ft_memalloc(sizeof(t_mlx_point))) == NULL)
		exit(0);
	new->num = 0;
	new->zoom = 1.0;
	new->x_zoom = (WIN_HEIGHT / 4) * (new->zoom * 0.0001);
	new->y_zoom = (WIN_WIDTH / 4) * (new->zoom * 0.0001);
	new->offset_x = 0.0;
	new->offset_y = 0.0;
	new->mlx.mlx_ptr = mlx_init();
	new->mlx.win = mlx_new_window(new->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT, "mxl 42");
	new->mlx.img.img_ptr = mlx_new_image(new->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT);
	new->mlx.img.data = (int *)mlx_get_data_addr(new->mlx.img.img_ptr,
	&new->mlx.img.bpp, &new->mlx.img.size_l, &new->mlx.img.endian);
	return (new);
}

int			main(int arc, char **arv)
{
	t_mlx_point	*new;

	new = init_new();
	if (arc == 2 && ft_strequ(arv[1], "mandelbrot") == 1)
	{
		new->num = 1;
		draw_fractal(&new);
	}
	if (arc == 2 && ft_strequ(arv[1], "julia") == 1)
	{
		new->num = 2;
		new->k = init_complex(-0.4, 0.6);
	}
	if (arc == 2 && ft_strequ(arv[1], "burning ship") == 1)
	{
		new->num = 3;
		draw_fractal(&new);
	}
	if (new->num == 0)
		put_help(arc, arv, new);
	mlx_hook(new->mlx.win, 2, 0, key_press, new);
	mlx_hook(new->mlx.win, 6, 0, mouse_move, new);
	mlx_loop(new->mlx.mlx_ptr);
	return (0);
}
