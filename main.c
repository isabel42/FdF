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


# include "fdf.h"



int ft_abs(int i)
{
	if (i < 0)
		return(-i);
	return(i);
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
	*(unsigned int*)dst = color;
}


void tracerSegment(t_data_img *img, int x1, int y1, int x2, int y2)
{
	int dx;
	int dy;
	int ex; // valeur d’erreur
	int ey; // valeur d’erreur
	int c;
	
	c = 0;
	if(x2 < x1)
	{
		c = x1;
		x1 = x2;
		x2 = c;
	}
	if(y2 < y1)
	{
		c = y1;
		y1 = y2;
		y2 = c;
	}
	ex  = x2 - x1;		// -e(0,1)
	ey  = y2 - y1;		// -e(0,1)
	dx = ex * 2 ;		  // -e(0,1)
	dy = ey * 2 ;  // e(1,0)
	if (ft_abs(x2 - x1) > ft_abs(y2 - y1))
	{
		while(x1 <= x2)
		{
			my_mlx_pixel_put(img, x1, y1, 0x0000FF00);
			x1 = x1 + 1 ;  // colonne du pixel suivant
			if ((ex = ex - dy) <= 0) // erreur pour le pixel suivant de même rangée
			{
				y1 = y1 + 1;  // choisir plutôt le pixel suivant dans la rangée supérieure
				ex = ex + dx;  // ajuste l’erreur commise dans cette nouvelle rangée
			} 
		}
	}
	else
	{
		while(y1 <= y2)
		{
			my_mlx_pixel_put(img, x1, y1, 0x000000FF);
			y1 = y1 + 1 ;  // colonne du pixel suivant
			if ((ey = ey - dx) <= 0) // erreur pour le pixel suivant de même rangée
			{
				x1 = x1 + 1;  // choisir plutôt le pixel suivant dans la rangée supérieure
				ey = ey + dy;  // ajuste l’erreur commise dans cette nouvelle rangée
			} 
		}
	}
  // Le pixel final (x2, y2) n’est pas tracé.
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data_img	img;
	// t_input		*data;

	if(argc != 2)
		return(0);
	printf("argv 1: %s\n", argv[1]);
	printf("pi: %f\n", M_PI);
	// data = ft_data(argv[1]);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	ft_printline(&img);//, data);
	// tracerSegment(&img, 50, 100, 25, 10);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	mlx_hook(vars.win, 17, 0, close_w, &vars);
	mlx_hook(vars.win, 2, 0, close_w, &vars);
	mlx_loop(vars.mlx);
}