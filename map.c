/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/23 02:52:24 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_countrow(char *argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(argv, O_RDONLY);
	ft_exit(fd);
	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_putstr_fd("File is empty!! \n", 1);
		exit(0);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close (fd);
	return (i);
}

t_input	*ft_data_create(t_input *data, char *argv)
{
	int		i;
	int		fd;

	i = 0;
	data->row = ft_countrow(argv);
	data->column = ft_countcolum(argv);
	data->input = ft_calloc(sizeof(data->input), data->row);
	data->map = malloc(sizeof(data->map) * data->row);
	data->a = 45 * (M_PI / 180);
	data->b = -30 * (M_PI / 180);
	fd = open(argv, O_RDONLY);
	ft_exit(fd);
	while (i < data->row)
	{
		data->input[i] = get_next_line(fd);
		data->map[i] = ft_calloc(data->column, sizeof(data->map));
		i++;
	}
	close(fd);
	return (data);
}

void	ft_data_alloc_line(char *input, int *map)
{
	int	a;
	int	k;

	a = 1;
	k = 0;
	while (input[0] && input[0] != '\n')
	{
		if ((input[0] > 47 && input[0] < 58) || input[0] == '-')
		{
			if (a == 1)
			{
				map[k] = ft_atoi(input);
				k++;
			}
			a = 0;
		}
		else
			a = 1;
		input++;
	}
}

t_input	*ft_data(char *argv)
{
	int		i;
	t_input	*data;

	i = 0;
	data = malloc(sizeof(data, argv));
	if (!data)
		exit(0);
	ft_data_create(data, argv);
	while (i < data->row)
	{
		ft_data_alloc_line(data->input[i], data->map[i]);
		i++;
	}
	data->zoom = ft_zoom(data);
	data->zoom_z = ft_zoom_z(data);
	return (data);
}
