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

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data_img	img;
	t_input		*data;
	t_iso		**iso;
	t_iso		*min;
	int			zoom;
	int			i = 0;
	int			j;

	if(argc != 2)
		return(0);
	
	data = ft_data(argv[1]);
	iso = ft_iso_pos(data);
	min = ft_is_min(iso, data);
	printf("xxx min.x: %f, min.y: %f\n", min->x, min->y);
	zoom = 1;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// ft_printline(&img, data);
	// tracer_segment(&img, (iso[0][0].x - min->x) * zoom, (iso[0][0].y - min->y)*zoom, (iso[10][0].x - min->x) *zoom, (iso[10][0].y - min->y) *zoom );
	// tracer_segment(&img, (iso[10][0].x - min->x) * zoom, (iso[10][0].y - min->y)*zoom, (iso[10][10].x - min->x) *zoom, (iso[10][10].y - min->y) *zoom );
	// tracer_segment(&img, (iso[10][10].x - min->x) * zoom, (iso[10][10].y - min->y)*zoom, (iso[0][10].x - min->x) *zoom, (iso[0][10].y - min->y) *zoom );
	// tracer_segment(&img, (iso[0][10].x - min->x) * zoom, (iso[0][10].y - min->y)*zoom, (iso[0][0].x - min->x) *zoom, (iso[0][0].y - min->y) *zoom );

	while (i < data->row)
	{
		j = 0;
		while(j < data->column - 1)
		{
			tracer_segment(&img, iso[i][j].x  * zoom, iso[i][j].y * zoom, iso[i][j + 1].x * zoom, iso[i][j + 1].y *zoom);
			if(i < data->row - 1)
				tracer_segment(&img, iso[i][j].x * zoom, iso[i][j].y * zoom, iso[i + 1][j].x * zoom, iso[i + 1][j].y * zoom);
			if(j == data->column - 2 && i < data->row - 1)
				tracer_segment(&img, iso[i][j + 1].x * zoom, iso[i][j + 1].y * zoom, iso[i + 1][j + 1].x * zoom, iso[i + 1][j + 1].y *zoom );
			j++;
		}
		i++;
	}
	my_mlx_pixel_put(&img, 0, 0, 0x000000FF);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 1920/4, 1080/4);

	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.mlx);
}