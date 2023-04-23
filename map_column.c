/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_column.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/04/23 02:52:44 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_exit(int fd)
{
	if (fd == -1)
	{
		perror("Error");
		exit (0);
	}
}

int	ft_countcolum_line(char *line)
{
	int		i;
	int		j;
	int		a;

	i = 0;
	a = 1;
	j = 0;
	while (line[i] != '\n')
	{
		if (line[i] > 47 && line[i] < 58 && a == 1)
		{
			j++;
			a = 0;
		}
		else
			a = 1;
		i++;
	}
	return (j);
}

int	ft_countcolum(char *argv)
{
	char	*line;
	int		fd;
	int		column;

	fd = open(argv, O_RDONLY);
	ft_exit(fd);
	line = get_next_line(fd);
	while (line)
	{
		column = ft_countcolum_line(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (column);
}
