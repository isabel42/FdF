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

typedef struct s_data_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_input {
	int		**map;
	int		row;
	int		column;
	float	a;
	float	b;
	int		zoom;
	float	zoom_z;
}				t_input;

typedef struct s_point {
	int		x;
	int		y;
}				t_point;

typedef struct s_bresen {
	int	incxi;
	int	incyi;
	int	incxr;
	int	incyr;
}			t_bresen;

typedef struct s_bresen_er {
	int	avr;
	int	av;
	int	avi;
}			t_bresen_er;

char		*get_until_nl(char *s, int loopret);
char		*ft_get_line(char *line, char *buf, int fd);
int			ft_totalloop(char *buf);
char		*ft_loopbuf(int looprep, char *buf);
char		*get_next_line(int fd);

char		*ft_testret(char *line, int ret, char *buf, int limit);
void		ft_free_cc(char **s);
void		ft_free_ii(int **s, int j);
void		ft_free_data(t_input *data);
void		ft_free_iso(t_point **iso, t_input *data);
void		ft_free_input(char **s, int j);

t_point		**ft_iso(t_input *data);
int			ft_is_min_x(t_point **iso, t_input *data);
int			ft_is_max_x(t_point **iso, t_input *data);
t_point		**ft_iso_pos(t_input *data);

void		ft_exit(int fd);
int			ft_countcolum_line(char *line);
int			ft_countrow(char **input);

char		**ft_readinput(char *argv);
int ft_countlines_input(char *argv);
t_input		*ft_data(char **input);
int			**ft_map(char **input);
void		ft_data_alloc_line(char *input, int *map);

void		my_mlx_pixel_put(t_data_img *data, int x, int y, int color);
t_bresen	*trace_segment_param(int x1, int y1, int x2, int y2);
int			trace_segment_dx(int x1, int y1, int x2, int y2);
int			trace_segment_dy(int x1, int y1, int x2, int y2);
t_bresen_er	*ft_error(t_point one, t_point two);

void		tracer_segment(t_data_img *img, t_point one, t_point two);

int			ft_abs(int a);
int			close_w(int keycode, t_vars *vars);
void		ft_image(t_input *data, t_data_img img);

t_point		**ft_iso_single(t_input *data);
float		ft_zoom(t_input *data);
float		ft_zoom_z(t_input *data);

#endif