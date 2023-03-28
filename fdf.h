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

char	*get_until_nl(char *s, int loopret);
char	*ft_get_line(char *line, char *buf, int fd);
int		ft_totalloop(char *buf);
char	*ft_loopbuf(int looprep, char *buf);
char	*get_next_line(int fd);
char	*ft_testret(char *line, int ret, char *buf, int limit);
void	ft_free(char *s);

int		ft_countrow(char *argv);
int		main(int argc, char **argv);

#endif