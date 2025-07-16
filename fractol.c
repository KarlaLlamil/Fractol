#include "fractol.h"
#include <stdio.h>

void	generate_palette(unsigned int palette[6])
{
    palette[0] = 0x20E0A2; // Green-Teal
    palette[1] = 0x1AE9DF; // Aqua-Cyan
    palette[2] = 0x358AEF; // Sky Blue
    palette[3] = 0x6A26CC; // Deep Purple
    palette[4] = 0xE432AD; // Hot Pink
	palette[5] = 0x00FFFFFF;
   // 0x000000  // Black
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp/ 8));
	*(unsigned int*)dst = color;
}

float converge_julia(int	x, int y, t_data *fractal)
{
	t_complex	z;
	int			iterations;
	double		temp;

	iterations = 0;

	z.i = fractal->window.min.i + ((double)y * (fractal->window.max.i - fractal->window.min.i))/HEIGHT;
	z.r = fractal->window.min.r + ((double)x * (fractal->window.max.r - fractal->window.min.r))/WIDTH;
	fractal->window.max_iter = 40;
	while (iterations < fractal->window.max_iter)
	{
		temp = z.r;
		z.r = (z.r*z.r) - (z.i * z.i) + fractal->c.r;
		z.i = 2*(temp * z.i) + fractal->c.i;
		if (sqrtf((z.r * z.r) + (-1*(z.i * z.i))) > 2)
			return (iterations); 
		++iterations;
	}
	return (-1);
}

float converge_mandelbrot(int	x, int y, t_data *fractal)
{
	t_complex	z;
	t_complex	c;
	int			iterations;
	double		temp;

	iterations = 0;
	z = (t_complex){};
	c.i = fractal->window.min.i + ((double)y * (fractal->window.max.i - fractal->window.min.i))/HEIGHT;
	c.r = fractal->window.min.r + ((double)x * (fractal->window.max.r - fractal->window.min.r))/WIDTH;
	while (iterations < fractal->window.max_iter)
	{
		temp = z.r;
		z.r = (z.r*z.r) - (z.i * z.i) + c.r;
		z.i = 2*(temp * z.i) + c.i;
		
		if ((z.r * z.r) + (z.i * z.i) > 4)
			return (iterations); 
		++iterations;
	}
	return (-1);

}

void	draw_fractal(t_data *fractal)
{
	t_coloring		pixel;
	unsigned int	palette[PALETTE_SIZE];

	pixel = (t_coloring){};
	generate_palette(palette);
	while (pixel.y < HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			if (fractal->type == MANDELBROT)
				pixel.iteration = converge_mandelbrot(pixel.x, pixel.y, fractal);
			else if (fractal->type == JULIA)
				pixel.iteration = converge_julia(pixel.x, pixel.y, fractal);
			if (pixel.iteration >= 0)
				my_mlx_pixel_put(&fractal->image, pixel.x, pixel.y, palette[pixel.iteration%5]);
			else
				my_mlx_pixel_put(&fractal->image, pixel.x, pixel.y, palette[5]);
			++pixel.x;
		}
		++pixel.y;
	}
	mlx_put_image_to_window(fractal->window.mlx, fractal->window.win, fractal->image.img,0,0);
}
