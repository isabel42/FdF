/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/16 21:52:43 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_tracer(t_bresen *param, t_bresen_er *error)
{
	free(param);
	free(error);
}

void	tracer_segment(t_data_img *img, t_point start, t_point end)
{
	t_bresen		*param;
	t_bresen_er		*error;
	t_point			one;
	t_point			two;

	one = start;
	two = end;
	param = trace_segment_param(one.x, one.y, two.x, two.y);
	error = ft_error(one, two);
	while ((one.x != two.x && param->incxr != 0)
		|| (one.y != two.y && param->incyr != 0))
	{
		my_mlx_pixel_put(img, one.x, one.y, 0x0000FFFF);
		if (error->av >= 0)
		{
			one.x = (one.x + param->incxi);
			one.y = (one.y + param->incyi);
			error->av = (error->av + error->avi);
			continue ;
		}
		one.x = (one.x + param->incxr);
		one.y = (one.y + param->incyr);
		error->av = (error->av + error->avr);
	}
	ft_free_tracer(param, error);
}
