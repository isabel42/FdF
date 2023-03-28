/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:45:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/28 11:01:27 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "minilibx/mlx.h"

# include "libft/libft.h"

typedef struct	s_data_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


// void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

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
	*(unsigned int*)dst = color;
}

void tracerSegment(t_data_img *img, int x1, int y1, int x2, int y2)
{
	int dx;
	int dy;
	int e; // valeur d’erreur
	
	e  = x2 - x1;        // -e(0,1)
	dx = e * 2 ;          // -e(0,1)
	dy = (y2 - y1) * 2 ;  // e(1,0)
	while(x1 <= x2)
	{
		my_mlx_pixel_put(img, x1, y1, 0x0000FF00);
		// tracerPixel(x1, y1) ;
    	x1 = x1 + 1 ;  // colonne du pixel suivant
    	if ((e = e - dy) <= 0) // erreur pour le pixel suivant de même rangée
      	{
			y1 = y1 + 1;  // choisir plutôt le pixel suivant dans la rangée supérieure
      		e = e + dx;  // ajuste l’erreur commise dans cette nouvelle rangée
		} 
	}
  // Le pixel final (x2, y2) n’est pas tracé.
}

int	main(void)
{
	t_vars	vars;
	t_data_img	img;
	int i;
	int j;

	i = 50;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while(i > 0)
	{
		j = (50 - i);
		while(j < 50 + (50 - i))
		{
			my_mlx_pixel_put(&img, 5 + j, 5 + i, 0x00FF0000);
			j++;	
		}
		i--;
	}
	tracerSegment(&img, 500, 10, 500, 100);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.mlx);
}