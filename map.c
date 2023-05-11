/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/10 22:17:11 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**ft_readinput(char *argv)
{
	char	**sol;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(argv, O_RDONLY);
	ft_exit(fd);
	line = get_next_line(fd);
	if (!line)
	{
		ft_putstr_fd("Input file is empty!\n", 1);
		exit(0);
	}
	sol = ft_start_malloc();
	while (line)
	{
		sol = ft_cc_c_join(sol, line, i);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (sol);
}

char	**ft_cc_c_join(char **cc, char *c, int i)
{
	char	**sol;
	char	*nul;
	int		j;

	j = 0;
	sol = malloc(sizeof(sol) * (i + 2));
	if (!sol)
		exit(0);
	nul = malloc(sizeof(nul));
	if (!nul)
		exit(0);
	nul[0] = '\0';
	while (j < i)
	{
		sol[j] = ft_strjoin(cc[j], nul);
		j++;
	}
	free(cc[j]);
	free(cc);
	sol[j] = ft_strjoin(c, nul);
	sol[j + 1] = malloc(sizeof(sol));
	sol[j + 1][0] = '\0';
	free(nul);
	return (sol);
}

t_input	*ft_data(char *argv)
{
	char	**input;
	t_input	*data;

	input = ft_readinput(argv);
	data = malloc(sizeof(data));
	if (!data)
		exit(0);
	data->map = ft_map(input);
	data->row = ft_countrow(input);
	data->column = ft_countcolum_line(input[0]);
	data->a = 45 * (M_PI / 180);
	data->b = -30 * (M_PI / 180);
	data->zoom = 40;
	data->zoom_z = 4;
	ft_free_cc(input);
	return (data);
}

int	**ft_map(char **input)
{
	int	i;
	int	**map;
	int	row;
	int	column;

	i = 0;
	row = ft_countrow(input);
	column = ft_countcolum_line(input[0]);
	map = malloc(sizeof(map) * row);
	if (!map)
		exit(0);
	while (i < row)
	{
		map[i] = malloc(column * sizeof(map));
		if (!map[i])
			exit(0);
		ft_data_alloc_line(input[i], map[i]);
		i++;
	}
	return (map);
}

void	ft_data_alloc_line(char *input, int *map)
{
	int	a;
	int	k;

	a = 1;
	k = 0;
	while (input[0] && input[0] != '\n')
	{
		if ((input[0] > 47 && input[0] < 58) || input[0] == '-')
		{
			if (a == 1)
			{
				map[k] = ft_atoi(input);
				k++;
			}
			a = 0;
		}
		else
			a = 1;
		input++;
	}
}
