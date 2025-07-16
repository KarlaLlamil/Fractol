#include "fractol.h"
#include <stdio.h>

int key(int keycode, t_data *fractal)
{

	if (keycode == XK_Escape)
		mlx_loop_end(fractal->window.mlx);
	return (0);
}

int	zoom(int button, int x, int y, t_data *fractal)
{
	t_complex	c;
	t_complex	len;
	double		zoom;
	t_complex	offset;

	len.r = fractal->window.max.r - fractal->window.min.r;
	len.i = fractal->window.max.i - fractal->window.min.i;
	c.i = fractal->window.min.i + ((double)y * (fractal->window.max.i - fractal->window.min.i))/HEIGHT;
	c.r = fractal->window.min.r + ((double)x * (fractal->window.max.r - fractal->window.min.r))/WIDTH;
	offset.r = (c.r - fractal->window.min.r)/len.r; 
	offset.i = (c.i - fractal->window.min.i)/len.i;
	if (button == 4)
		zoom = 0.9;
	else if (button == 5)
		zoom = 1.1;
	else
		return (0);
	fractal->window.min.r = c.r -(offset.r *len.r* zoom);
	fractal->window.min.i = c.i -(offset.i *len.i* zoom);
	fractal->window.max.r = fractal->window.min.r+ (len.r*zoom);
	fractal->window.max.i = fractal->window.min.i + (len.i*zoom);
	draw_fractal(fractal);
	return (0);
}
