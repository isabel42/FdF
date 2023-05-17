/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/17 14:33:44 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_zoom(char **input)
{
	t_point	size;
	int		row;
	int		column;
	float	b;
	float	zoom;

	row = ft_countrow(input);
	column = ft_countcolum_line(input[0]);
	b = -30 * (M_PI / 180);
	size.x = ft_abs(column * cos(b)) + ft_abs(row * cos(90 * (M_PI / 180) + b));
	size.y = ft_abs(column * sin(b)) + ft_abs(row * sin(90 * (M_PI / 180) + b));
	zoom = 1710.0 / size.x;
	if (zoom > 930.0 / size.y)
		zoom = 930.0 / size.y;
	return (zoom);
}

int	ft_is_max_map(int row, int column, int **map)
{
	int		i;
	int		j;
	int		max_map;

	i = 0;
	max_map = 0;
	while (i < row)
	{
		j = 0;
		while (j < column)
		{
			if (ft_abs(map[i][j]) > max_map)
				max_map = ft_abs(map[i][j]);
			j++;
		}
		i++;
	}
	return (max_map);
}

float	ft_zoom_z(char **input)
{
	int		max_map;
	int		**map;
	int		row;
	int		column;

	map = ft_map(input);
	row = ft_countrow(input);
	column = ft_countcolum_line(input[0]);
	max_map = ft_is_max_map(row, column, map);
	ft_free_ii(map, row);
	if (max_map == 0)
		return (1);
	return (50.0 / max_map);
}
