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

void	ft_image(t_input *data, t_data_img img)
{
	t_point		**iso;
	int			i;
	int			j;

	iso = ft_iso_pos(data);
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
}

void	ft_image_2(t_data_img img)
{
	// t_point		**iso;
	// int			i;
	// int			j;

	// iso = ft_iso_pos(data);
	// i = 0;
	my_mlx_pixel_put(&img, 500, 500, 0x00FFFFFF);
	// while (i < data->row)
	// {
	// 	j = 0;
	// 	while (j < data->column - 1)
	// 	{
	// 		tracer_segment(&img, iso[i][j], iso[i][j + 1]);
	// 		if (i < data->row - 1)
	// 			tracer_segment(&img, iso[i][j], iso[i + 1][j]);
	// 		if (j == data->column - 2 && i < data->row - 1)
	// 			tracer_segment(&img, iso[i][j + 1], iso[i + 1][j + 1]);
	// 		j++;
	// 	}
	// 	i++;
	// }
}


int	main(int argc, char **argv)
{
	t_input		*data;
	char		**input;
	t_vars		vars;
	t_data_img	img;
	t_point		**iso;

	if (argc != 2)
	{
		ft_putstr_fd("Incorrect number of aguments\n", 1);
		return (0);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "FdF");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	input = ft_readinput(argv[1]);
	data = ft_data(input);
	iso = ft_iso(data);
	printf("row: %d\n", data->row);
	printf("alpha: %f\n", data->a);
	printf("beta: %f\n", data->b);
	printf("iso.x: %d\n", iso[0][0].x);
	ft_image(data, img);
	printf("test\n");
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 210, 90);
	// mlx_hook(vars.win, 17, 0, close_w, &vars);
	// mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.mlx);
}

// int	main(int argc, char **argv)
// {
// 	t_input		*data;
// 	t_vars		vars;
// 	t_data_img	img;

// 	if (argc != 2)
// 	{
// 		ft_putstr_fd("Incorrect number of aguments\n", 1);
// 		return (0);
// 	}
// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "FdF");
// 	img.img = mlx_new_image(vars.mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
// 			&img.line_length, &img.endian);
// 	data = ft_data(argv[1]);
// 	ft_image(data, img);
// 	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 210, 90);
// 	mlx_hook(vars.win, 17, 0, close_w, &vars);
// 	mlx_hook(vars.win, 2, 0, close_w, &vars);
// 	mlx_loop(vars.mlx);
// }
