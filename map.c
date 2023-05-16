/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/16 17:00:52 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int ft_countlines_input(char *argv)
{
	int		fd;
	int		i;
	char	*line;
	
	i = 0;
	fd = open(argv, O_RDONLY);
	ft_exit(fd);
	line = get_next_line(fd);
	if (!line || line == NULL)
	{
		ft_putstr_fd("Input file is empty!\n", 1);
		exit(0);
	}
	while (line != NULL)
	{
		i++;
		// free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	**ft_readinput(char *argv)
{
	char	**sol;
	int		fd;
	char	*line;
	int		i;

	sol = malloc(sizeof(sol) * ft_countlines_input(argv) + 1);
	fd = open(argv, O_RDONLY);
	ft_exit(fd);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		//sol[i] = ft_strcpy(line);
		sol[i] = ft_strjoin(line, "\0");
		line = get_next_line(fd);
		i++;
	}
	sol[i] = NULL;
	close (fd);
	// int y = ft_countlines_input(argv) + 1;
	// int aa = 0;
	// while(aa < y){
	// 	printf("%s",sol[aa]);
	// 	aa++;
	// }
	return(sol);
}

t_input	*ft_data(char **input)
{
	t_input	*data;

	data = malloc(sizeof(*data));
	if (!data)
		exit(0);
	data->map = ft_map(input);
	data->row = ft_countrow(input);
	data->column = ft_countcolum_line(input[0]);
	data->a = 45 * (M_PI / 180);
	data->b = -30 * (M_PI / 180);
	data->z = 40;
	data->z_z = 2;
	return (data);
}

int	**ft_map(char **input)
{
	int	i;
	int	**map;
	int	row;
	int	column;

	i = 0;
	row = ft_countrow(input);
	column = ft_countcolum_line(input[0]);
	map = (int **)malloc(sizeof(*map) * row);
	if (!map)
		exit(0);
	while (i < row)
	{
		map[i] = (int*)malloc(column * sizeof(*map[i]));
		if (!map[i])
			exit(0);
		ft_data_alloc_line(input[i], map[i]);
		i++;
	}
	return (map);
}

void	ft_data_alloc_line(char *input, int *map)
{
	int	a;
	int	k;
	int	i;

	a = 1;
	k = 0;
	i = 0;
	while (input[i] != '\n' && input[i] != '\0')
	{
		if ((input[i] > 47 && input[i] < 58) || input[i] == '-')
		{
			if (a == 1)
			{
				map[k] = ft_atoi(input + i);
				k++;
			}
			a = 0;
		}
		else
			a = 1;
		i++;
	}
}
