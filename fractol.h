#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include <math.h>
# include "ft_printf_git/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <pthread.h>
# define WIN_WIDTH 768
# define WIN_HEIGHT 768
# define COORD_X (WIN_WIDTH / 2)
# define COORD_Y (WIN_HEIGHT / 5)
# define COEF_PLUS 2
# define COEF_MINUS 2
# define COEF_MOVE 20
# define UP_DOWN 10
# define DELTA 1
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


typedef struct		s_coord
{
	int			x;
	int			y;
	int				color;
}					t_coord;

typedef struct		s_mlx_point
{
	t_coord			*copy;
	int				x;
	int				y;
	t_mnim			k;
	int				x_zoom;
	int				y_zoom;
	int				*colors;
	int				size;
	int				num;
	t_mlx			mlx;
	double				zoom;
}					t_mlx_point;
void julia(int x, int y,t_mlx_point **new);
void	draw_fractal(t_mlx_point **new);


#endif