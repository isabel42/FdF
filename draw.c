/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:14:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/29 22:47:40 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_printline(t_data_img *img)//, t_input *data)
{
	// int x1;
	// int y1;
	// int x2;
	// int y2;
	// int i;
	// int j;

	// i = 0;
	// while (i < data->row - 1)
	// {
	// 	j = 0;
	// 	while(j < data->column - 1)
	// 	{
	// 		x1 = sqrt(2)/2 * (i - j) * 10 * j;
	// 		y1 = (sqrt(2/3) * data->map[i][j] - 1/sqrt(6) * (i + j)) * 10 * j;
	// 		x2 = sqrt(2)/2 * (i - j + 2) * 10 * (j + 1);
	// 		y2 = sqrt(2/3) * data->map[i + 1][j + 1] - (1/sqrt(6) * (i + j + 2)) * 10 * (j + 1) ;
	// 		// printf("x1: %d\n", x1);
	// 		// printf("y1: %d\n", y1);
	// 		// printf("x2: %d\n", x2);
	// 		// printf("y2: %d\n", y2);
	// 		// printf("endian img: %d\n", img->endian);
	// 		tracerSegment(img, x1 + 500, y1 + 500 , x2 + 500, y2 + 500);
	// 		j++;
	// 	}
	// 	i++;
	// }
	tracerSegment(img, 100, 100 , 100, 200);
	tracerSegment(img, 100, 200 , 200, 200);
	// tracerSegment(img, 200, 200 , 200, 100);
	// tracerSegment(img, 200, 100 , 100, 100);

	tracerSegment(img, sqrt(2)/2 * (100 - 100) +1000, -1/sqrt(6) * (100 + 100) +1000, sqrt(2)/2 * (100 - 200)  +1000, -1/sqrt(6) * (100 + 200) +1000);
	tracerSegment(img, sqrt(2)/2 * (100 - 200) +1000, -1/sqrt(6) * (100 + 200) +1000, sqrt(2)/2 * (200 - 200)  +1000, -1/sqrt(6) * (200 + 200) +1000);
	//tracerSegment(img, sqrt(2)/2 * (200 - 200)  +1000, -1/sqrt(6) * (200 + 200) +1000, sqrt(2)/2 * (200 - 100)  +1000, -1/sqrt(6) * (200 + 100) +1000);
	//tracerSegment(img, sqrt(2)/2 * (200 - 100) +1000, -1/sqrt(6) * (200 + 100) +1000, sqrt(2)/2 * (100 - 100)  +1000, -1/sqrt(6) * (100 + 100) +1000);
}