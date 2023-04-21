/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/06 17:24:21 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**ft_iso_single(t_input *data)
{
	t_point	**iso;
	int		i;
	int		j;

	i = 0;
	iso = malloc (sizeof(iso) * data->row);
	if (!iso)
		exit(0);
	while (i < data->row)
	{
		iso[i] = malloc (sizeof(iso) * data->column);
		if (!iso)
			exit(0);
		j = 0;
		while (j < data->column)
		{
			iso[i][j].x = (j * cos(data->b) + i * sin(data->b));
			iso[i][j].y = (-j * sin (data->a) * sin(data->b))
				- 0 * data->map[i][j] * cos(data->a) + i * sin(data->a) * cos(data->b);
			j++;
		}
		i++;
	}
	return (iso);
}

float	ft_zoom(t_input *data)
{
	t_point	**iso_single;
	t_point	*min;
	t_point	*max;
	t_point	*size;
	int		zoom;

	iso_single = ft_iso_single(data);
	min = ft_is_min(iso_single, data);
	max = ft_is_max(iso_single, data);
	size = malloc(sizeof(size) * 1);
	if (!size)
		exit(0);
	size->x = ft_abs(max->x - min->x);
	size->y = ft_abs(max->y - min->y);
	zoom = 1500 / size->x;
	if(zoom > 900 / size->y)
		zoom = 900 / size->y;
	if (zoom > 40)
		zoom = 40;
	free(min);
	free(max);
	free(size);
	free(iso_single);
	return(zoom);
}

float	ft_zoom_z(t_input *data)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while(i < data->row)
	{
		j = 0;
		while(j < data->column)
		{
			if (ft_abs(data->map[i][j]) > max)
				max = ft_abs(data->map[i][j]);
			j++;
		}
		i++;
	}
	if (max == 0)
		return (0);
	return (40.0 / max);
}
