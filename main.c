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

void	ft_image_2(int x, int y, t_data_img img)
{
	// printf("iso 00.x: %d\n", iso[0][0].x);
	my_mlx_pixel_put(&img, x, y, 0x0000FFFF);
}

void	ft_image_3(int row, int column, t_point **iso, t_data_img img)
{
	int			i;
	int			j;

	i = 0;
	while (i < row && i < 1)
	{
		j = 0;
		while (j < column - 1)
		{
			tracer_segment(&img, iso[i][j], iso[i][j + 1]);
			if (i < row - 1)
				tracer_segment(&img, iso[i][j], iso[i + 1][j]);
			if (j == column - 2 && i < row - 1)
				tracer_segment(&img, iso[i][j + 1], iso[i + 1][j + 1]);
			j++;
		}
		i++;
	}
}

void	ft_image(t_input *data, t_data_img img)
{{
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
}
}


int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data_img	img;
	t_input		*data;
	char		**input;
	t_point		**iso;

	if (argc != 2)
	{
		ft_putstr_fd("Incorrect number of aguments\n", 1);
		return (0);
	}
	input = ft_readinput(argv[1]);
	printf("\n");
	data = ft_data(input);
	/*
	for (int i = 0; i < data->row; i++){
		for (int y = 0; y < data->column; y++)
		{
			printf("%d  ", data->map[i][y]);
		}
		printf("\n");
	}
	*/
	iso = ft_iso(data);
			printf("row: %d\n", data->row);
			printf("alpha: %f\n", data->a);
			printf("beta: %f\n", data->b);
			printf("iso.x: %d\n", iso[0][0].x);
			printf("iso.y: %d\n", iso[0][0].y);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "FdF");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	ft_image(data, img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.mlx);
}