/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/30 15:39:18 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_iso	*ft_iso(int x, int y, int z)
{
	t_iso *coord;

	coord = malloc (sizeof(coord) * 1);
	if (!coord)
		exit(0);
	coord->x = (x - y) * cos(30 / (180 * M_PI));
	coord->y = (-z + x + y) * sin (30 / (180 * M_PI));
	return (coord);
}


void ft_printline(t_data_img *img, t_input *data)
{
	int i;
	int j;

	t_iso *start;
	t_iso *end;
	t_iso *end_end;
	i = 0;
	while(i < data->column)
	{
		j = 0;
		while(j < data->row)
		{
			if(i < data->column -1)
			{
				start = ft_iso(i + (20 * i), j + (20 * j), data->map[j][i]);
				end = ft_iso((i + 1) + (20 * (i + 1)), j + (20 * j), data->map[j][i + 1]);
				tracerSegment(img, i + (20 * i), j + (20 * j), (i + 1) + (20 * (i + 1)), j + (20 * j));
				free(start);
				free(end);
			}
			if(j < data->row -1 )
			{
				start = ft_iso(i + (20 * i), j + (20 * j), data->map[j][i]);
				end_end = ft_iso(i + (20 * i), (j + 1) + (20 * (j + 1)), data->map[j][i + 1]);
				tracerSegment(img, i + (20 * i), j + (20 * j), i + (20 * i), (j + 1) + (20 * (j + 1)));
				free(start);
			}
			j++;
		}
		i++;
	}
	my_mlx_pixel_put(img, 0, 0, 0x00FF0000);
}