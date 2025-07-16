#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "stdbool.h"
# include <stdlib.h>
# include "mlx/mlx.h"
# include "X11/keysym.h"

#define PALETTE_SIZE 6
#define WIDTH 1360
#define HEIGHT 700

typedef struct s_image 
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef	struct s_window
{
	void	*win;
	void	*mlx;
	t_complex	max;
	t_complex	min;
	int		max_iter;
}	t_window;

typedef	enum e_type
{
	MANDELBROT,
	JULIA,
	INVALID
}	t_type;

typedef struct s_data
{
	t_window	window;
	t_image		image;
	t_type		type;
	t_complex	c;
}	t_data;

typedef struct s_coloring
{
	int	y;
	int	x;
	int iteration;
}	t_coloring;

int key(int keycode, t_data *window);
void	validate_args(int argc, char **argv, t_data *fractal);
void	draw_fractal(t_data *fractal);
int	zoom(int button, int x, int y, t_data *fractal);
void	init_data(t_data *fractal, int argc, char **argv);

#endif
