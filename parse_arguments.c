#include "fractol.h"
#include <unistd.h>
#include <stdio.h>

bool ft_int(char *str, double *integer, double *decimal)
{
	int		count;
	bool	point;

	count = 1;
	point = false;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			if (point == false)
				*integer = *integer * 10 + *str - '0';
			else
			{
				*decimal = *decimal * 10 + *str - '0';
				count = count * 10;
			}
		}
		else if (point == false && *str == '.')
			point = true;
		else
			return(false);
		++str;
	}
	*decimal = *decimal/count;
	return (true);
}

bool	ft_atod(char	*str, t_data *fractal, bool real)
{
	double	integer;
	double	decimal;
	double	sign;

	sign = 1;
	decimal = 0;
	integer = 0;
	if (str[0] == '+')
		++str;
	else if (str[0] == '-')
	{
		sign = -1;
		++str;
	}
	if (!ft_int(str, &integer, &decimal))
		return (false);
	if (real == true)
		fractal->c.r = sign * (integer + decimal);
	else
		fractal->c.i = sign * (integer + decimal);
	return(true);
}

int	ft_strcmp(const char *string1, const char *string2)
{
	size_t	i;

	i = 0;
	while ((string1[i] != '\0') || (string2[i] != '\0'))
	{
		if (string1[i] == string2[i])
			++i;
		else
			return ((unsigned char)string1[i] - (unsigned char)string2[i]);
	}
	return (0);
}

void print_instructions(void)
{
	write(2, "Error:\n",6);

}

void	validate_args(int argc, char **argv, t_data *fractal)
{
	if (argc == 2 && ft_strcmp(argv[1], "Mandelbrot") == 0)
		fractal->type = MANDELBROT;
	else if ((argc == 2 || argc == 4) && ft_strcmp(argv[1], "Julia") == 0)
	{
		if (argc == 2)
		{
			fractal->c.r = 0.285;
			fractal->c.i = 0.01;
			fractal->type = JULIA;
		}
		else
		{
			if (ft_atod(argv[2], fractal, true) && ft_atod(argv[3], fractal, false))
				fractal->type = JULIA;
			else
			{
				print_instructions();
				fractal->type = INVALID;
			}
		}
	}
	else
	{
		print_instructions();
		fractal->type = INVALID;
	}
}
void	init_data(t_data *fractal, int argc, char **argv)
{
	fractal->window.max.r = 2.0;
	fractal->window.max.i = 1.5;
	fractal->window.min.r = -2.0;
	fractal->window.min.i = -1.5;
	fractal->window.max_iter = 40;
	validate_args(argc, argv, fractal);
	printf("real = %f imaginary = %f", fractal->c.r, fractal->c.i);
}
