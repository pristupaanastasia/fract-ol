#include "fractol.h"
int		key_press(int keykode, t_mlx_point *param)
{
	(void)param;
	if (keykode == 53)
		exit(0);
	return (0);
}

/*void ft_zoom(int x,int y,t_mlx_point *new)
{

	int i;
	int j;
	int *win;
	i = y;
	win = malloc(WIN_HEIGHT * WIN_WIDTH *sizeof(int));
	y = WIN_HEIGHT - y;
	while (i < WIN_HEIGHT)
	{
    	j = x;
   		while (j < WIN_WIDTH)
   		{
			
		}
	}
}*/

/*int		mouse_press(int button, int x, int y, t_mlx_point *param)
{
	(void)x;
	(void)y;
	
	(void)param;
	button = 1;
	//param = render(param);
	if (button == 5)
	{
		//ft_bzero(param->mlx.img.data,sizeof(sizeof(param->mlx.img.data)));
		param->zoom = param->zoom -0.01;
		//if (param->num == 2)
		//	julia(param->x,param->y,param);
		//if (param->num == 1)
		//	draw_fractal(param);

	}
	if (button == 4)
	{
		//ft_bzero(param->mlx.img.data,sizeof(sizeof(param->mlx.img.data)));
		param->zoom = param->zoom + 0.01;
		//if (param->num == 2)
		//	julia(param->x,param->y,param);
		//if (param->num == 1)
		//	draw_fractal(param);		
	}

	return (0);
}*/

int			mouse_move(int x, int y, t_mlx_point *param)
{

//	if ((x - param->x) * (x - param->x) > 1000 || (y - param->y) * (y - param->y) > 1000)
//	{
	
		param->x = x;
		param->y = WIN_HEIGHT - y;
		//printf("PARAM %d\n",param->num);
		if (param->num == 2)
			julia(param->x,param->y,param);
//	}
	return (0);
}

/*int			mouse_release(int button, int x, int y, t_mlx_point *param)
{
	(void)x;
	(void)y;
 
	return (0);
}*/
t_mnim init_complex(double re, double im)
{
    t_mnim complex;
    
    complex.re = re;
    complex.im = im;
    return (complex);
}

void	draw_fractal(t_mlx_point *new)
{
	int max_iteration = 50;
	t_mnim min;
	t_mnim max;
	t_mnim fractol;
	t_mnim c;
	int iteration;
	t_mnim z;
	double t;
	int lol;
	int green;
	int red;
	int blue;
	lol=0;
	printf("num %d\n",new->num);
	min = init_complex(-2.0, -2.0);
	max.re = 2.0;
	max.im = min.im + (max.re - min.re) * WIN_HEIGHT / WIN_WIDTH;
	fractol = init_complex((max.re - min.re) / (WIN_WIDTH - 1),(max.im - min.im) / (WIN_HEIGHT - 1));
	int y = 0;
	int x = 0;
	while (y < WIN_HEIGHT)
	{
    	c.im = max.im - y * fractol.im;
    	x = 0;
   		while (x < WIN_WIDTH )
   		{
        c.re = min.re + x * fractol.re;
        z = init_complex(c.re, c.im);
        iteration = 0;
		while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && iteration < max_iteration)
        {
			if (new->num == 2)
			{ 	printf("ALIVE\n");
				c.im = new->k.im;
				c.re = new->k.re;
			}
            z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0) + c.re,
                2.0 * z.re * z.im + c.im);
            iteration++;
        }
        t = (double)iteration / (double)max_iteration;
		//printf("k %d",k);
		red = (int)(9 * (1 - t) * pow(t, 3) * 255);
		green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
		blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
		new->mlx.img.data[lol++] = red << 16 | green << 8 | blue;
   		}
    y++;
	}
	mlx_put_image_to_window(new->mlx.mlx_ptr, new->mlx.win,
		new->mlx.img.img_ptr, 0, 0);
}
void julia(int x, int y,t_mlx_point *new)
{
	//printf("julia\n");
	//printf("NUM %d \n",new->num);
	ft_bzero(new->mlx.img.data,sizeof(sizeof(new->mlx.img.data)));
	new->k = init_complex(
        4 * ((double)x / WIN_WIDTH - 0.5),
        4 * ((double)(WIN_HEIGHT - y) /WIN_HEIGHT - 0.5));
    draw_fractal(new);
}
int		main(int arc, char **arv)
{
	t_mlx_point	*new;

	if ((new = (t_mlx_point*)ft_memalloc(sizeof(t_mlx_point))) == NULL)
		exit(0);
//	ft_bzero(new, sizeof(t_mlx_point));
	new->num = 0;
	new->zoom = 1.0;
	new->mlx.mlx_ptr = mlx_init();
	new->mlx.win = mlx_new_window(new->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT, "mxl 42");
	new->mlx.img.img_ptr = mlx_new_image(new->mlx.mlx_ptr,
	WIN_WIDTH, WIN_HEIGHT);
	new->mlx.img.data = (int *)mlx_get_data_addr(new->mlx.img.img_ptr,
	&new->mlx.img.bpp, &new->mlx.img.size_l, &new->mlx.img.endian);
	if (arc == 2 && ft_strequ(arv[1],"mandelbrot") == 1)
	{
		printf("KEK\n");
		new->num = 1;
		draw_fractal(new);
	}
	if (arc == 2 && ft_strequ(arv[1],"julia") == 1)
	{
		new->num = 2;
		new->k = init_complex(-0.4, 0.6);
	}
	mlx_hook(new->mlx.win, 2, 0, key_press, new);
	//mlx_hook(new->mlx.win, 4, 0, mouse_press, new);
	//mlx_hook(new->mlx.win, 5, 0, mouse_release, new);
	mlx_hook(new->mlx.win, 6, 0, mouse_move, new);
	mlx_loop (new->mlx.mlx_ptr);
	return (0);
}
