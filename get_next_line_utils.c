/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:09:38 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/10 17:47:42 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_testret(char *line, int ret, char *buf, int limit)
{
	if (ret < limit)
	{
		buf[0] = '\0';
		free(line);
		return (NULL);
	}
	return (line);
}

void	ft_free_cc(char **s)
{
	int	i;

	i = 0;
	while (s[i] && s[i][0] != '\0')
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
}

void	ft_free_ii(int **s, int j)
{
	int	i;

	i = 0;
	while (s[i]&& i < j)
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