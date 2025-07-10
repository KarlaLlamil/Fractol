#include <mlx.h>
#include "fractol.h"
#include <math.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hola ");

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// initiate window rendering 
	mlx_loop(mlx);
}

