/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/21 04:09:31 by itovar-n         ###   ########.fr       */
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
	if (fd == -1)
	{
		perror("Error");
		exit (0);
	}
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

int	ft_countcolum_line(char *line)
{
	int		i;
	int		j;
	int		a;

	i = 0;
	a = 1;
	j = 0;
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
	return (j);
}

int	ft_countcolum(char *argv)
{
	char	*line;
	int		fd;
	int		column;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit (0);
	}
	line = get_next_line(fd);
	while(line)
	{
		column = ft_countcolum_line(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (column);
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
	if (fd == -1)
	{
		perror("Error");
		exit (0);
	}
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
	int a;
	int k;

	a = 1;
	k = 0;
	while (input[0] && input[0] != '\n')
	{
		if ((input[0] > 47 && input[0] < 58) || input[0] == '-') 
		{
			if(a == 1)
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
