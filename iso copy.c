/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/06 15:36:54 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_z_zoom(t_input *data)
{
	int		i;
	int		j;
	float 	max;
	float	z_zoom;

	i = 0;
	max = 0;
	while(i < data->row)
	{
		j = 0;
		while(j < data->column)
		{
			if(ft_abs(data->map[i][j]) > max)
				max = ft_abs(data->map[i][j]);
			j++;
		}
		i++;
	}
	z_zoom = i / max;
	if(z_zoom > j / max)
		z_zoom = j / max;
	return(z_zoom);
}

 void ft_iso_line(int i, t_input *data, t_point *iso, float z_zoom)
{
	int j;

	j = 0;
	while (j < data->column)
	{
		iso[j].x = (j * cos(data->beta) + i * sin(data->beta));
		iso[j].y = (-j * sin (data->alpha) * sin(data->beta))
			- z_zoom * data->map[i][j] * cos(data->alpha) + i * sin(data->alpha) * cos(data->beta);
		j++;
	}

}

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
			iso[i][j].x = (j * cos(data->beta) + i * sin(data->beta));
			iso[i][j].y = (-j * sin (data->alpha) * sin(data->beta))
				- data->map[i][j] * cos(data->alpha) + i * sin(data->alpha) * cos(data->beta);
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

float	ft_zoom(t_point **iso, t_input *data)
{
	t_point	*min;
	t_point	*max;
	t_point	*size;
	float		zoom;

	min = ft_is_min(iso, data);
	max = ft_is_max(iso, data);
	size = malloc(sizeof(size) * 1);
	if (!size)
		exit(0);
	size->x = ft_abs(max->x - min->x);
	size->y = ft_abs(max->y - min->y);
	zoom = 1500 / size->x;
	if(zoom > 900 / size->y)
		zoom = 900 / size->y;
	free(min);
	free(max);
	free(size);
	printf("zoom: %f\n", zoom);
	return(zoom);
}

t_point	**ft_iso_pos(t_input *data)
{
	t_point	**iso;
	t_point	**iso_pos;
	t_point	*min;
	float	zoom;
	int		i;
	int		j;

	i = 0;
	iso = ft_iso(data);
	min = ft_is_min(iso, data);
	zoom = 1; //ft_zoom(iso, data);
	iso_pos = malloc (sizeof(iso_pos) * data->row);
	if (!iso_pos)
		exit(0);
	while (i < data->row)
	{
		iso_pos[i] = malloc (sizeof(iso_pos) * data->column);
		if (!iso_pos)
			exit(0);
		j = 0;
		while (j < data->column)
		{
			iso_pos[i][j].x = zoom * (j * cos(data->beta) + i * sin(data->beta) - min->x);
			iso_pos[i][j].y = zoom * ((-j * sin (data->alpha) * sin(data->beta)
				-  data->map[i][j] * cos(data->alpha) + zoom * i * sin(data->alpha) * cos(data->beta)) - min->y);
			j++;
		}
		i++;
	}
	printf("i: %d - j: %d\n", i, j);
	return (iso_pos);
}
