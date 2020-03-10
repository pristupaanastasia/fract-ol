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
	int			*mas;
	t_mnim		*mnim;

	mas = malloc(4 * sizeof(int));
	mnim = malloc(6 * sizeof(t_mnim));
	init_draw(&mnim, &mas, new);
	while (mas[2] < new->end)
	{
		mnim[3].im = ((mnim[1].im - mas[2] * mnim[2].im) * new->zoom);
		mas[3] = 0;
		while (mas[3] < WIN_WIDTH)
		{
			mnim[3].re = ((mnim[0].re + mas[3] * mnim[2].re) * new->zoom);
			mnim[4] = init_complex(mnim[3].re, mnim[3].im);
			mas[1] = 0;
			while (pow(mnim[4].re, 2.0) +
			pow(mnim[4].im, 2.0) <= 4 && mas[1] < mas[0])
				mnim[4] = init_z(new, mnim[4], mnim[3], mas);
			new->mlx.img.data[mas[2] * (WIN_HEIGHT) +
			mas[3]] = color_fractol(mas[1], mas[0]);
			mas[3]++;
		}
		mas[2]++;
	}
	free_mass(mnim, mas);
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
	new->x_zoom = WIN_HEIGHT / 2;
	new->y_zoom = WIN_WIDTH / 2;
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
	mlx_hook(new->mlx.win, 4, 0, mouse_press, new);
	mlx_hook(new->mlx.win, 6, 0, mouse_move, new);
	mlx_loop(new->mlx.mlx_ptr);
	return (0);
}
