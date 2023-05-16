/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/16 17:02:21 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**ft_iso(t_input *dt)
{
	t_point	**iso;
	int		i;
	int		j;

	i = 0;
	iso = (t_point **)malloc(sizeof(*iso) * dt->row);
	if (!iso)
		exit(0);
	while (i < dt->row)
	{
		iso[i] = (t_point *)malloc(sizeof(*iso[i]) * dt->column);
		if (!iso[i])
			exit(0);
		j = 0;
		while (j < dt->column)
		{
			iso[i][j].x = dt->z * (j * cos(dt->b) + i * sin(dt->b));
			iso[i][j].y = dt->z * (sin(dt->a) * (i * cos(dt->b) - j
						* sin(dt->b))) - dt->z_z * dt->map[i][j] * cos(dt->a);
			j++;
		}
		i++;
	}
	ft_iso_pos(iso, dt);
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

void	ft_iso_pos(t_point **iso, t_input *data)
{
	int		i;
	int		j;
	int		min_x;
	int		min_y;

	min_x = ft_is_min_x(iso, data);
	min_y = ft_is_min_y(iso, data);
	i = 0;
	while (i < data->row)
	{
		j = 0;
		while (j < data->column)
		{
			iso[i][j].x = iso[i][j].x - min_x;
			iso[i][j].y = iso[i][j].y - min_y;
			j++;
		}
		i++;
	}
}
