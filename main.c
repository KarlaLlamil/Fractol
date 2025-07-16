#include "fractol.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	fractal;

	fractal = (t_data){};
	init_data(&fractal, argc, argv);
	if(fractal.type == INVALID)
	  	return (1);
	fractal.window.mlx = mlx_init();
	if (fractal.window.mlx == NULL)
	 	return (1);
 	fractal.window.win = mlx_new_window(fractal.window.mlx, WIDTH, HEIGHT, argv[1]);
 	fractal.image.img = mlx_new_image(fractal.window.mlx, WIDTH, HEIGHT);
 	fractal.image.addr = mlx_get_data_addr(fractal.image.img, &fractal.image.bpp, &fractal.image.line_length, &fractal.image.endian);
	mlx_hook(fractal.window.win, 2, 1L<<0, key, &fractal);
 	mlx_hook(fractal.window.win, 17, 1L<<2, mlx_loop_end, fractal.window.mlx);
	mlx_mouse_hook(fractal.window.win, zoom, &fractal);
 	draw_fractal(&fractal);
 	mlx_loop(fractal.window.mlx);
 	mlx_destroy_image(fractal.window.mlx, fractal.image.img);
 	mlx_destroy_window(fractal.window.mlx, fractal.window.win);
 	mlx_destroy_display(fractal.window.mlx);
	free(fractal.window.mlx);
	return (0);
}
