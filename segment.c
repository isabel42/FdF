/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/05 12:27:39 by itovar-n         ###   ########.fr       */
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

void	tracer_segment(t_data_img *img, t_point start, t_point end)
{
	t_bresen	*param;
	int			avr;
	int			av;
	int			avi;
	t_point		one;
	t_point		two;

	one = start;
	two = end;
	param = trace_segment_param(one.x, one.y, two.x, two.y);
	avr = (2 * trace_segment_dy(one.x, one.y, two.x, two.y));
	av = (avr - trace_segment_dx(one.x, one.y, two.x, two.y));
	avi = (av - trace_segment_dx(one.x, one.y, two.x, two.y));
	while ((one.x != two.x && param->incxr != 0) || (one.y != two.y && param->incyr != 0))
	{
	printf("one.x: %d - ", one.x);
	printf("one.y: %d\n", one.y);
		my_mlx_pixel_put(img, one.x, one.y, 0x00FFFFFF);
		if (av >= 0)
		{
			one.x = (one.x + param->incxi);
			one.y = (one.y + param->incyi);
			av = (av + avi);
			continue ;
		}
		one.x = (one.x + param->incxr);
		one.y = (one.y + param->incyr);
		av = (av + avr);
	}
	free(param);
}
