/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   fdf.h											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: itovar-n <marvin@42lausanne.ch>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/03/28 15:29:13 by itovar-n		  #+#	#+#			 */
/*   Updated: 2023/03/28 18:25:50 by itovar-n		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
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

typedef struct	s_input {
	char	**input;
	int		**map;
	int		row;
	int		*column;
}				t_input;

typedef struct	s_iso {
	float		x;
	float		y;
}				t_iso;

typedef struct s_bresen {
	// int	dX;
	// int	dY;
	int	IncXi;
	int	IncYi;
	int	IncXr;
	int	IncYr;
}			t_bresen;

char	*get_until_nl(char *s, int loopret);
char	*ft_get_line(char *line, char *buf, int fd);
int		ft_totalloop(char *buf);
char	*ft_loopbuf(int looprep, char *buf);
char	*get_next_line(int fd);
char	*ft_testret(char *line, int ret, char *buf, int limit);
void	ft_free_cc(char **s);

int		ft_countrow(char *argv);
int	*ft_countcolum(char *argv);
t_input	*ft_data_create(t_input *data, char *argv);
t_input	*ft_data(char *argv);
void ft_data_alloc_line(char *input, int *map, int j, int k);


void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color);
void tracer_segment(t_data_img *img, int x1, int y1, int x2, int y2);
int		main(int argc, char **argv);

#endif