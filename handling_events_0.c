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
	//printf("keycode = %i", keycode);
	len.r = fractal->window.max.r - fractal->window.min.r;
	len.i = fractal->window.max.i - fractal->window.min.i;
	c.i = fractal->window.min.i + ((double)y * (fractal->window.max.i - fractal->window.min.i))/HEIGHT;
	c.r = fractal->window.min.r + ((double)x * (fractal->window.max.r - fractal->window.min.r))/WIDTH;
	if (button == 4)
		zoom = 0.9;
	else if (button == 5)
		zoom = 1.1;
	else
		return (0);
	fractal->window.max.r = c.r + (len.r * zoom)/2;
	fractal->window.max.i = c.i + (len.i * zoom)/2;
	fractal->window.min.r = c.r - (len.r * zoom)/2;
	fractal->window.min.i = c.i - (len.i * zoom)/2;
	draw_fractal(fractal);
	return (0);
}
