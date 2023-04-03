/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/30 21:19:10 by itovar-n         ###   ########.fr       */
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
	//free(line);
	return (j);
}

int	*ft_countcolum(char *argv)
{
	char	*line;
	int		fd;
	int		*column;
	int		i;

	i = 0;
	column = malloc(sizeof(column)* ft_countrow(argv));
	if (!column)
		exit(0);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		exit (0);
	line = get_next_line(fd);
	while(line)
	{
		column[i] = ft_countcolum_line(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	return (column);
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
		ft_data_alloc_line(data->input[i], data->map[i], 0, 0);
		i++;
	}
	return (data);
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
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		exit (0);
	while (i < data->row)
	{
		data->input[i] = get_next_line(fd);
		data->map[i] = ft_calloc(data->column[i], sizeof(data->map));
		i++;
	}
	close(fd);
	return (data);
}

void	ft_data_alloc_line(char *input, int *map, int j, int k)
{
	int	result;
	int	a;

	result = 0;
	a = 1;
	while (input[j] && input[j] != '\n')
	{
		if (input[j] > 47 && input[j] < 58)
		{
			a = 0;
			result = result * 10 + (input[j] - 48);
		}
		else
			result = 0;
		j++;
		if ((!input[j] || (input[j] < 48 || input[j] > 57)) && a == 0)
		{
			a = 1;
			map[k] = result;
			k++;
		}
	}
}
