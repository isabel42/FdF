/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/23 02:36:35 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**ft_iso(t_input *data)
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
			iso[i][j].x = data->zoom * (j * cos(data->b) + i * sin(data->b));
			iso[i][j].y = data->zoom * (-j * sin (data->a) * sin(data->b))
				- data->zoom_z * data->map[i][j] * cos(data->a)
				+ data->zoom * i * sin(data->a) * cos(data->b);
			j++;
		}
		i++;
	}
	return (iso);
}

t_point	*ft_is_min(t_point **iso, t_input *data)
{
	int		i;
	int		j;
	t_point	*min;

	i = 0;
	min = malloc(sizeof(min) * 1);
	if (!min)
		exit(0);
	min->x = 0;
	min->y = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->column)
		{
			if (iso[i][j].x < min->x)
				min->x = iso[i][j].x;
			if (iso[i][j].y < min->y)
				min->y = iso[i][j].y ;
			j++;
		}
		i++;
	}
	return (min);
}

t_point	*ft_is_max(t_point **iso, t_input *data)
{
	int		i;
	int		j;
	t_point	*max;

	i = 0;
	max = malloc(sizeof(max) * 1);
	if (!max)
		exit(0);
	max->x = 0;
	max->y = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->column)
		{
			if (iso[i][j].x > max->x)
				max->x = iso[i][j].x;
			if (iso[i][j].y > max->y)
				max->y = iso[i][j].y;
			j++;
		}
		i++;
	}
	return (max);
}

t_point	**ft_iso_pos(t_input *data)
{
	t_point	*min;
	t_point	**iso;
	int		i;
	int		j;

	iso = ft_iso(data);
	min = ft_is_min(iso, data);
	i = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->column)
		{
			iso[i][j].x = iso[i][j].x - min->x;
			iso[i][j].y = iso[i][j].y - min->y;
			j++;
		}
		i++;
	}
	free(min);
	return (iso);
}
