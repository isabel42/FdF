/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/03 13:28:06 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_iso	**ft_iso(t_input *data)
{
	t_iso **iso;
	int i;
	int j;
	float alpha = 30 * (M_PI / 180);
	float beta =  45 * (M_PI / 180);

	i = 0;
	iso = malloc (sizeof(iso) * data->row);
	if (!iso)
		exit(0);
	while (i < data->row)
	{ 
		iso[i] = malloc (sizeof(iso) *  data->column[i]);
		if (!iso)
			exit(0);
		j = 0;
		while (j <  data->column[i])
		{
			iso[i][j].x = (j * cos(beta) + data->map[i][j] * sin(beta)) * 10;
			iso[i][j].y= (-j * sin (alpha) * sin(beta) + i * cos(alpha) + data->map[i][j] * sin(alpha) * cos(beta)) * 10 ;
			j++;
		}
		i++;
	}
	return (iso);
}

t_iso *ft_is_min(t_iso **iso, t_input *data)
{

	int i;
	int j;
	t_iso *min;

	i = 0;
	min = malloc(sizeof(min) * 1);
	if(!min)
		exit(0);
	*min = iso[0][0];
	while(i < data->row)
	{
		j = 0;
		while(j < data->column[i])
		{
			if(iso[i][j].x < min->x)
				iso[i][j].x = min->x;
			if(iso[i][j].y < min->y)
				iso[i][j].y = min->y;
			j++;
		}
		i++;
	}
	return (min);
}


