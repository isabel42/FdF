/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: itovar-n <marvin@42lausanne.ch>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/03/22 11:45:55 by itovar-n		  #+#	#+#			 */
/*   Updated: 2023/03/28 18:26:07 by itovar-n		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	close_w(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Incorrect number of aguments\n", 1);
		exit (0);
	}
}

void	ft_image(t_input *data, t_data_img img)
{
	t_point		**iso;
	int			i;
	int			j;

	iso = ft_iso(data);
	i = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->column - 1)
		{
			tracer_segment(&img, iso[i][j], iso[i][j + 1]);
			if (i < data->row - 1)
				tracer_segment(&img, iso[i][j], iso[i + 1][j]);
			if (j == data->column - 2 && i < data->row - 1)
				tracer_segment(&img, iso[i][j + 1], iso[i + 1][j + 1]);
			j++;
		}
		i++;
	}
	ft_free_iso(iso, data);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data_img	img;
	t_input		*data;
	char		**input;

	ft_check_argc(argc);
	input = ft_readinput(argv[1]);
	data = ft_data(input);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "FdF");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	ft_image(data, img);
	ft_free_cc(input);
	ft_free_data(data);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.mlx);
	free(img.img);
	return (0);
}
