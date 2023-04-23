/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/23 03:37:22 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset + (data->bits_per_pixel / 8);
	*(unsigned int *) dst = color;
}

t_bresen	*trace_segment_param(int x1, int y1, int x2, int y2)
{
	t_bresen	*param;

	param = malloc(sizeof(param));
	if (!param)
		exit(0);
	if (y2 - y1 >= 0)
		param->incyi = 1;
	else
		param->incyi = -1;
	if (x2 - x1 >= 0)
		param->incxi = 1;
	else
		param->incxi = -1;
	if (ft_abs(x2 - x1) >= ft_abs(y2 - y1))
	{
		param->incxr = param->incxi;
		param->incyr = 0;
	}
	else
	{
		param->incxr = 0;
		param->incyr = param->incyi;
	}
	return (param);
}

int	trace_segment_dx(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	k;

	dy = ft_abs(y2 - y1);
	dx = ft_abs(x2 - x1);
	if (dx < dy)
	{
		k = dx;
		dx = dy;
		dy = k;
	}
	return (dx);
}

int	trace_segment_dy(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	k;

	dy = ft_abs(y2 - y1);
	dx = ft_abs(x2 - x1);
	if (dx < dy)
	{
		k = dx;
		dx = dy;
		dy = k;
	}
	return (dy);
}

t_bresen_er	*ft_error(t_point one, t_point two)
{
	t_bresen_er	*error;

	error = malloc(sizeof(error));
	if (!error)
		exit(0);
	error->avr = (2 * trace_segment_dy(one.x, one.y, two.x, two.y));
	error->av = (error->avr - trace_segment_dx(one.x, one.y, two.x, two.y));
	error->avi = (error->av - trace_segment_dx(one.x, one.y, two.x, two.y));
	return (error);
}
