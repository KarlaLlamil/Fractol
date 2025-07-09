#include "minilibx-linux/mlx.h"

int main (void)
{
	void	*mlx;
	void	*mlx_win;

// establish a connetion to the correct graphicl systems, and returna void * which holds
// our current MLX instance
	mlx = mlx_init();
// intialize a window which stays open
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hola ");
// initiate window rendering 
	mlx_loop(mlx);

// bpp -> bits per pixel (pixels basically ints?) how many bit color in my cpu, cpu Byte Order = Little Endian
// memory address to mutate the bytes?
	return (0);
}