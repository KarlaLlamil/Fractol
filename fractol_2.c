#include "fractol.h"
#include <stdio.h>

unsigned int palette[PALETTE_SIZE] = {
    0x20E0A2, // Green-Teal
    0x1AE9DF, // Aqua-Cyan
    0x358AEF, // Sky Blue
    0x6A26CC, // Deep Purple
    0xE432AD, // Hot Pink
    0x000000  // Black
};

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp/ 8));
	*(unsigned int*)dst = color;
}

float converge(int	x, int y, t_window *window)
{
	t_complex	z;
	t_complex	c;
	double		r;
	int			iterations;
	double		temp;
	double		zn;
	double		nu;
	double		smooth;

	
//	r = pow(10, 8);
	iterations = 0;
	z = (t_complex){};
	c.i = -1.5 + ((double)y * (1.5 + 1.5))/window->y;
	c.r = -2.0 + ((double)x * (2.0 + 2.0))/window->x;
	while (iterations < 2000)
	{
		temp = z.r;
		z.r = (z.r*z.r) - (z.i * z.i) + c.r;
		z.i = 2*(temp * z.i) + c.i;
		
		if ((z.r * z.r) + (z.i * z.i) > 4)
		{
			double zn = log(z.r*z.r + z.i*z.i) / 2.0;
    		double nu = log(zn / log(2)) / log(2);
    		iterations = iterations + 1 - nu;
		//	printf("z = %f + %fi\n x = %i y = %i\n",z.r, z.i, x, y );
			return (iterations); 
		}
		++iterations;
	}
	return (-1);

}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int adjust_color_brightness(int color, float factor)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

	factor = factor/2000;
    r = fminf(255, fmaxf(0, r * factor));
    g = fminf(255, fmaxf(0, g * factor));
    b = fminf(255, fmaxf(0, b * factor));

    return (r << 16 | g << 8 | b);
}
unsigned int lerp_color(unsigned int c1, unsigned int c2, float t)
{
    int r1 = (c1 >> 16) & 0xFF;
    int g1 = (c1 >> 8) & 0xFF;
    int b1 = c1 & 0xFF;

    int r2 = (c2 >> 16) & 0xFF;
    int g2 = (c2 >> 8) & 0xFF;
    int b2 = c2 & 0xFF;

    int r = r1 + t * (r2 - r1);
    int g = g1 + t * (g2 - g1);
    int b = b1 + t * (b2 - b1);

    return (r << 16 | g << 8 | b);
}

void	draw_fractal(t_data *img, t_type fractal, t_window *window)
{
	int	y;
	int	x;
	int iteration;
	unsigned int purple;
	unsigned int colour;
	float t;
	float	scaled;
	float	blend;
	int index;

	x = 0;
	y = 0;
	purple = create_trgb(0, 128, 0, 128);
	while (y < window->y)
	{
		x = 0;
		while (x < window->x)
		{
			iteration = converge(x, y, window);
			if (iteration >= 0)
			{
				t = (double)iteration/2000;
				//printf ("%f,	", t);
				scaled = t *(PALETTE_SIZE - 1);
				index = (int)scaled;
				blend = scaled - index;
				index = (int)iteration%6;
				if (index >= PALETTE_SIZE - 1)
					colour = palette[PALETTE_SIZE -1];
				else
					colour= lerp_color(palette[index], palette[index + 1],blend);
//				purple = adjust_color_brightness (purple, iteration);
				my_mlx_pixel_put(img, x, y, colour);
			}
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(window->mlx, window->win, img->img,0,0);
//	printf("end\n");
}