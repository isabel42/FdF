/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:09:38 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/17 14:28:52 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_cc(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_free_ii(int **s, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_free_data(t_input *data)
{
	ft_free_ii(data->map, data->row);
	free(data);
}

void	ft_free_iso(t_point **iso, t_input *data)
{
	int	i;

	i = 0;
	while (i < data->row)
	{
		free(iso[i]);
		i++;
	}
	free(iso);
}
