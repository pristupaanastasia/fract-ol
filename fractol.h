/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:29:53 by mriley            #+#    #+#             */
/*   Updated: 2020/03/10 18:29:57 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include <math.h>
# include "ft_printf_git/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# define WIN_WIDTH 768
# define WIN_HEIGHT 768
# define COEF_PLUS 2
# define COEF_MINUS 2
# define COEF_MOVE 20
# define UP_DOWN 10
# define DELTA 1
# define COLOR_SILVER		0xCCCCCC

typedef struct		s_mnim
{
	double re;
	double im;
}					t_mnim;

typedef struct		s_img
{
	void			*img_ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win;
	t_img			img;
}					t_mlx;

typedef struct		s_mlx_point
{
	int				x;
	int				y;
	t_mnim			k;
	int				x_zoom;
	int				y_zoom;
	int				start;
	int				end;
	int				size;
	int				num;
	t_mlx			mlx;
	double			zoom;
}					t_mlx_point;

void				julia(int x, int y, t_mlx_point **new);
void				draw_fractal(t_mlx_point **new);
t_mnim				init_z(t_mlx_point *new, t_mnim z, t_mnim c, int *it);
int					color_fractol(int it, int max);
double				interpolate(double start, double end, double interpolation);
t_mnim				init_complex(double re, double im);
void				draw_help(t_mlx_point *new);
int					mouse_move(int x, int y, t_mlx_point *param);
int					mouse_press(int button, int x, int y, t_mlx_point *param);
int					key_press(int keykode, t_mlx_point *param);
void				draw_fractal_part(t_mlx_point *new);
void				julia(int x, int y, t_mlx_point **new1);
t_mlx_point			*init_new(void);
void				init_draw(t_mnim **mnim1, int **mas1, t_mlx_point *new);
void				free_mass(t_mnim *mnim1, int *mas1);
void				put_help(int arc, char **s, t_mlx_point *new);

#endif
