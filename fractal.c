#include "fractol.h"
int		key_press(int keykode, t_mlx_point *param)
{
	(void)param;
	if (keykode == 53)
		exit(0);
	return (0);
}

int		mouse_press(int button, int x, int y, t_mlx_point *param)
{
	param->x_zoom = x;
	param->y_zoom = WIN_HEIGHT - y;
	if (button == 5)
	{
		if (param->zoom > 0.05)
			param->zoom = param->zoom - 0.05;
		else
		{
			if (param->zoom > 0.005)
				param->zoom = param->zoom / 2;
		}
			if (param->num == 2)
				julia(param->x,param->y,&param);
			if (param->num != 2)
			{
				ft_bzero(param->mlx.img.data,sizeof(sizeof(param->mlx.img.data)));
				draw_fractal(&param);
			}
	}
	if (button == 4)
	{
		param->zoom = param->zoom + 0.05;
		if (param->num == 2)
			julia(param->x,param->y ,&param);
		if (param->num !=2)
		{
			ft_bzero(param->mlx.img.data,sizeof(sizeof(param->mlx.img.data)));
			draw_fractal(&param);
		}		
	}
	return (0);
}

int			mouse_move(int x, int y, t_mlx_point *param)
{
	param->x = x;
	param->y = WIN_HEIGHT - y;
	if (param->num == 2)
		julia(param->x,param->y,&param);
	return (0);
}

t_mnim init_complex(double re, double im)
{
    t_mnim complex;
    
    complex.re = re;
    complex.im = im;
    return (complex);
}

double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int		color_fractol(int it,int max)
{
	double t;
	int red;
	int green;
	int blue;

	t = (double)it / (double)max;
	red = (int)(9 * (1 - t) * pow(t, 3) * 255);
	green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
	return(red << 16 | green << 8 | blue);
}

void draw_fractal_part(t_mlx_point *new)
{
	int max_iteration = 50;
	t_mnim min;
	t_mnim max;
	t_mnim fractol;
	t_mnim c;
	int iteration;
	t_mnim z;
	t_mnim mouse;
	min = init_complex(-2.0, -2.0);
	max.re = 2.0;
	max.im = min.im + (max.re - min.re) * WIN_HEIGHT / WIN_WIDTH;
	fractol = init_complex((max.re - min.re) / (WIN_WIDTH - 1),(max.im - min.im) / (WIN_HEIGHT - 1));
	mouse = init_complex((double)new->x_zoom/(WIN_WIDTH /max.re-min.re) + min.re,(double)new->y_zoom / (WIN_HEIGHT / max.im - min.im) * -1 + max.im);
	min.re = interpolate(mouse.re, min.re, 1.0/ new->zoom);
	min.im = interpolate(mouse.im, min.im, 1.0/ new->zoom);
	max.re = interpolate(mouse.re, max.re, 1.0/ new->zoom);
	max.im = interpolate(mouse.im, max.im, 1.0/ new->zoom);
	int y = new->start;
	int x = 0;
	while (y < new->end)
	{
    	c.im = ((max.im - y * fractol.im) * new->zoom); 
    	x = 0;
   		while (x < WIN_WIDTH)
   		{
        c.re = ((min.re + x * fractol.re)* new->zoom); 
        z = init_complex(c.re, c.im);
        iteration = 0;
		while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && iteration < max_iteration)
        {
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
            iteration++;
        }
		new->mlx.img.data[y * (WIN_HEIGHT) + x] = color_fractol(iteration,max_iteration);
		x++;
   		}
    y++;
	}
}
void	draw_fractal(t_mlx_point **new1)
{
	pthread_t	threads[10];
	t_mlx_point	fractols[10];
	t_mlx_point *new;
	new = *new1;
	int i = 0;
	while (i < 10)
	{
		fractols[i] = *new;
		fractols[i].start = i * (WIN_HEIGHT / 10);
		fractols[i].end = (i + 1) * (WIN_HEIGHT / 10);
		pthread_create(&threads[i],NULL,(void *(*)(void *))draw_fractal_part,(void *)&fractols[i]);
		i++;
	}
	while(i-- > 0)
	{
		pthread_join(threads[i], NULL);
	}
	mlx_put_image_to_window(new->mlx.mlx_ptr, new->mlx.win,
		new->mlx.img.img_ptr, 0, 0);
}
void julia(int x, int y,t_mlx_point **new1)
{
	t_mlx_point *new;

	new = *new1;
	ft_bzero(new->mlx.img.data,sizeof(sizeof(new->mlx.img.data)));
	new->k = init_complex(
        ((double)x / WIN_WIDTH - 0.5),
         ((double)y /WIN_HEIGHT - 0.5 ));
    draw_fractal(new1);
}

void draw_help(t_mlx_point *new)
{
	ft_bzero(new->mlx.img.data,
		WIN_WIDTH * WIN_HEIGHT * (new->mlx.img.bpp/ 8));
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

void init_new(t_mlx_point	*new)
{
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
}

int		main(int arc, char **arv)
{
	t_mlx_point	*new;

	if ((new = (t_mlx_point*)ft_memalloc(sizeof(t_mlx_point))) == NULL)
		exit(0);
	init_new(new);
	if (arc == 2 && ft_strequ(arv[1],"mandelbrot") == 1)
	{
		new->num = 1;
		draw_fractal(&new);
	}
	if (arc == 2 && ft_strequ(arv[1],"julia") == 1)
	{
		new->num = 2;
		new->k = init_complex(-0.4, 0.6);
	}
	if (arc == 2 && ft_strequ(arv[1],"burning ship") == 1)
	{
		new->num = 3;
		draw_fractal(&new);
	}
	if ((arc == 2 && ft_strequ(arv[1],"-help") == 1))
		draw_help(new);
	if (arc != 2 || new->num == 0)
	{
		ft_printf("Use flags:\n		burning ship \n		julia \n		mandelbrot\n");
		exit(0);
	}
	mlx_hook(new->mlx.win, 2, 0, key_press, new);
	mlx_hook(new->mlx.win, 4, 0, mouse_press, new);
	mlx_hook(new->mlx.win, 6, 0, mouse_move, new);
	mlx_loop (new->mlx.mlx_ptr);
	return (0);
}
