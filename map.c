/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   map.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: itovar-n <marvin@42lausanne.ch>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/03/28 17:47:51 by itovar-n		  #+#	#+#			 */
/*   Updated: 2023/03/28 18:29:27 by itovar-n		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

int	ft_countrow(char *argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		exit (0);
	line = get_next_line(fd);
	if (line == NULL)
		exit(0);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close (fd);
	return (i);
}

char	*ft_getfirstline(char *argv)
{
	char	*line;
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		exit (0);
	line = get_next_line(fd);
	close(fd);
	return (line);
}

int	ft_countcolum(char *argv)
{
	int		i;
	int		j;
	int		a;
	char	*line;

	i = 0;
	j = 0;
	a = 1;
	line = ft_getfirstline(argv);
	while (line[i] != '\n')
	{
		if (line[i] > 47 && line[i] < 58 && a == 1)
		{
			j++;
			a = 0;
		}
		else
			a = 1;
		i++;
	}
	free(line);
	return (j);
}

int	**ft_map(char **input, int **map)
{
	int	i;
	int	j;
	int	k;
	int	result;

	i = 0;
	k = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j] == '\n')
		{
			if (input[i][j] > 47 && input[i][j] < 58)
				result = result * 10 + input[i][j] + 48;
			else
				result = 0;
			j++;
			if (input[i][j] == '\n' || input[i][j] < 48 || input[i][j] > 57)
			{
				map[i][k] = result;
				k++;
			}
		}
	}
	return (map);
}

int	**ft_input(char *argv)
{
	char	**input;
	int		**map;
	int		row;
	int		i;
	int		fd;

	i = 0;
	row = ft_countrow(argv);
	input = ft_calloc(sizeof(input), row);
	map = ft_calloc(sizeof(map), row);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		exit (0);
	printf("row: %d\n", row);
	while (i < row)
	{
	//printf("gnl: %s", get_next_line(fd));
		//input[i] = get_next_line(fd);
		map[i] = ft_calloc(ft_countcolum(argv), sizeof(map));
		i++;
	}
	//map = ft_map(input, map);
	//ft_free_cc(input);
	return (map);
}


