/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/16 10:28:07 by itovar-n         ###   ########.fr       */
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
		if (!iso[i])
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

int	ft_is_min_x(t_point **iso, t_input *data)
{
	int		i;
	int		j;
	int		min_x;

	i = 0;
	min_x = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->column)
		{
			if (iso[i][j].x < min_x)
				min_x = iso[i][j].x;
			j++;
		}
		i++;
	}
	return (min_x);
}

int	ft_is_min_y(t_point **iso, t_input *data)
{
	int		i;
	int		j;
	int		min_y;

	i = 0;
	min_y = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->column)
		{
			if (iso[i][j].y < min_y)
				min_y = iso[i][j].y;
			j++;
		}
		i++;
	}
	return (min_y);
}

int	ft_is_max_x(t_point **iso, t_input *data)
{
	int		i;
	int		j;
	int		max_x;

	i = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->column)
		{
			if (iso[i][j].x > max_x)
				max_x = iso[i][j].x;
			j++;
		}
		i++;
	}
	return (max_x);
}

t_point	**ft_iso_pos(t_input *data)
{
	t_point	**iso;
	t_point	**iso_pos;
	int		i;
	int		j;

	iso = ft_iso(data);
	iso_pos = malloc(sizeof(iso_pos) * data->row);
	if(!iso_pos)
		exit(0);
	i = 0;
	while (i < data->row)
	{
		iso_pos[i] = malloc(sizeof(iso_pos) * data->column);
		if(!iso_pos[i])
			exit(0);
		j = 0;
		while (j < data->column)
		{
			iso_pos[i][j].x = iso[i][j].x - ft_is_min_x(iso, data);
			iso_pos[i][j].y = iso[i][j].y - ft_is_min_y(iso, data);
			j++;
		}
		i++;
	}
	ft_free_iso(iso, data);
	return (iso_pos);
}
