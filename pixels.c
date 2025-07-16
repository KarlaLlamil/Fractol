
#include "fractol.h"
#include <stdio.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

bool converge(int	x, int y, t_window size)
{
	t_complex	z;
	t_complex	c;
	double		r;
	int			iterations;
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;

	r = pow(10, 8);
	iterations = 0;
	min_x = -2.0;
	max_x = 2.0;
	min_y = -1.5;
	max_y = 1.5;
	z = (t_complex){};
	c.i = min_y + ((double)y * (max_y - min_y))/size.y;
	c.r = min_x + ((double)x * (max_x - min_x))/size.x;
	while (iterations < 500)
	{
		z.r = (z.r*z.r) - (z.i * z.i) + c.r;
		z.i = 2*(z.r * z.i) + c.i;
		if ((z.r * z.r) + (z.i * z.i) > r)
			return (false); 
		++iterations;
	}
	return (true);

}

int	main(void)
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;
	t_window size;
	

	size.x = 1360;
	size.y = 700;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, size.x, size.y, "Fractol");

	img.img = mlx_new_image(mlx, size.x, size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
//	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
			if (converge(x,y, size))
			{
				printf("true\n");
				my_mlx_pixel_put(&img, x, y, 0x00FF0000);
			}
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// initiate window rendering 
	mlx_loop(mlx);
	
}

