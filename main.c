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

int ft_abs(int 	a)
{
	if (a < 0)
		return(-a);
	return(a);
}

int	close_w(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset + (data->bits_per_pixel / 8);
	*(unsigned int *) dst = color;
}

t_bresen	*trace_segment_param(int x1, int y1, int x2, int y2)
{
	t_bresen	*param;

	param = malloc(sizeof(param));
	if (!param)
		exit(0);
	if (y2 - y1 >= 0)
		param->IncYi = 1;
	else
		param->IncYi = -1;
	if (x2 - x1 >= 0)
		param->IncXi = 1;
	else
		param->IncXi = -1;
	if (ft_abs(x2 - x1) >= ft_abs(y2 - y1))
	{
		param->IncXr = param->IncXi;
		param->IncYr = 0;
	}
	else
	{
		param->IncXr = 0;
		param->IncYr = param->IncYi;
	}
	return (param);
}

int	trace_segment_dx(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	k;

	dy = ft_abs(y2 - y1);
	dx = ft_abs(x2 - x1);
	if (dx < dy)
	{
		k = dx;
		dx = dy;
		dy = k;
	}
	return (dx);
}

int	trace_segment_dy(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	k;

	dy = ft_abs(y2 - y1);
	dx = ft_abs(x2 - x1);
	if (dx < dy)
	{
		k = dx;
		dx = dy;
		dy = k;
	}
	return (dy);
}

void	tracer_segment(t_data_img *img, int x1, int y1, int x2, int y2)
{
	t_bresen	*param;
	int			avr;
	int			av;
	int			avi;

	param = trace_segment_param(x1, y1, x2, y2);
	avr = (2 * trace_segment_dy(x1, y1, x2, y2));
	av = (avr - trace_segment_dx(x1, y1, x2, y2));
	avi = (av - trace_segment_dx(x1, y1, x2, y2));
	while ((x1 != x2 && param->IncXr != 0) || (y1 != y2 && param->IncYr != 0))
	{
		// printf("x1: %d - y1: %d - avr: %d\n", x1, y1, avr);
		my_mlx_pixel_put(img, x1, y1, 0x00FFFFFF);
		if (av >= 0)
		{
			x1 = (x1 + param->IncXi);
			y1 = (y1 + param->IncYi);
			av = (av + avi);
			continue ;
		}
		x1 = (x1 + param->IncXr);
		y1 = (y1 + param->IncYr);
		av = (av + avr);
	}
	free(param);
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
	iso = ft_iso(data);
	min = ft_is_min(iso, data);
	zoom = 30;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// ft_printline(&img, data);
	// tracer_segment(&img, (iso[0][0].x - min->x) * zoom, (iso[0][0].y - min->y)*zoom, (iso[10][0].x - min->x) *zoom, (iso[10][0].y - min->y) *zoom );
	// tracer_segment(&img, (iso[10][0].x - min->x) * zoom, (iso[10][0].y - min->y)*zoom, (iso[10][10].x - min->x) *zoom, (iso[10][10].y - min->y) *zoom );
	// tracer_segment(&img, (iso[10][10].x - min->x) * zoom, (iso[10][10].y - min->y)*zoom, (iso[0][10].x - min->x) *zoom, (iso[0][10].y - min->y) *zoom );
	// tracer_segment(&img, (iso[0][10].x - min->x) * zoom, (iso[0][10].y - min->y)*zoom, (iso[0][0].x - min->x) *zoom, (iso[0][0].y - min->y) *zoom );

	while (i < data->row - 1)
	{
		j = 0;
		while(j < data->column[i] - 1)
		{
			tracer_segment(&img, (iso[i][j].x - min->x) * zoom, (iso[i][j].y - min->y)*zoom, (iso[i][j + 1].x - min->x) *zoom, (iso[i][j + 1].y - min->y) *zoom );
			if(i < data->row - 2)
				tracer_segment(&img, (iso[i][j].x - min->x) * zoom, (iso[i][j].y - min->y)*zoom, (iso[i + 1][j].x - min->x) *zoom, (iso[i + 1][j].y - min->y) *zoom );
			if(j == data->column[i] - 2 && i < data->row - 2)
				tracer_segment(&img, (iso[i][j].x - min->x) * zoom, (iso[i][j].y - min->y)*zoom, (iso[i][j + 1].x - min->x) *zoom, (iso[i][j + 1].y - min->y) *zoom );
			j++;
		}
		i++;
	}

	printf("iso 0-0.x: %f\n", iso[0][0].x);
	printf("iso 0-0.y: %f\n", iso[0][0].y  -min->y);
	printf("iso 10-0.x: %f\n", iso[10][0].x * 5);
	printf("iso 10-0.y: %f\n", (iso[10][0].y -min->y) * 5);
	printf("iso 10-10.x: %f\n",(iso[10][10].x * 5));
	printf("iso 10-10.y: %f\n", (iso[10][10].y -min->y) * 5);
	printf("iso 0-10.x: %f\n", iso[0][10].x * 5);
	printf("iso 0-10.y: %f\n", (iso[0][10].y -min->y) * 5);
	my_mlx_pixel_put(&img, 0, 0, 0x000000FF);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 1920/4, 1080/4);

	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.mlx);
}