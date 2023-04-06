/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/06 16:31:29 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_zoom(t_point **iso, t_input *data)
{
	t_point	*min;
	t_point	*max;
	t_point	*size;
	float		zoom;

	min = ft_is_min(iso, data);
	max = ft_is_max(iso, data);
	zoom = 1;
	size = malloc(sizeof(size) * 1);
	if (!size)
		exit(0);
	size->x = ft_abs(max->x - min->x);
	size->y = ft_abs(max->y - min->y);
	printf("size.y: %d\n", size->y);
	zoom = 900 / size->x;
	if(zoom > 1500 / size->y)
		zoom = 1500 / size->y;
	free(min);
	free(max);
	free(size);
	return(zoom);
}

t_point	**ft_iso_single(t_input *data)
{
	t_point	**iso;
	int		i;
	int		j;
	float	a = 45 * (M_PI / 180);
	float	b = -30 * (M_PI / 180);
	int		z = 1;

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
			iso[i][j].x = z * (j * cos(b) + i * sin(b));
			iso[i][j].y = z  * (-j * sin (a) * sin(b))
				- data->map[i][j] * cos(a) + z * i * sin(a) * cos(b);
			j++;
		}
		i++;
	}
	return (iso);
}

t_point	**ft_iso(t_input *data)
{
	t_point	**iso;
	t_point	**iso_single;
	int		i;
	int		j;
	float	a = 45 * (M_PI / 180);
	float	b = -30 * (M_PI / 180);
	int		z;

	i = 0;
	iso_single = ft_iso_single(data);
	z = ft_zoom(iso_single, data);
	printf("zoom calc: %f\n", ft_zoom(iso_single, data));
	// z = 15;
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
			iso[i][j].x = z * (j * cos(b) + i * sin(b));
			iso[i][j].y = z  * (-j * sin (a) * sin(b))
				- data->map[i][j] * cos(a) + z * i * sin(a) * cos(b);
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
	printf("min.x min y: %d, %d\n", min->x, min->y);

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
	printf("iso00: %d, %d\n", iso[0][0].x, iso[0][0].y);
	free(min);
	return (iso);
}
