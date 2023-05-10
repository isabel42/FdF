/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_column.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:15:46 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/10 18:11:56 by itovar-n         ###   ########.fr       */
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

char	**ft_start_malloc()
{
	char	**sol;

	sol = malloc(sizeof(sol));
	if (!sol)
		exit(0);
	sol[0] = malloc(sizeof(sol));
	if (!sol[0])
		exit(0);
	return(sol);
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

int	ft_countrow(char **input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i][j] && input[i][j] != '\0')
	{
		if(input[i][j] == '\n')
		{
			j = 0;
			if(!input[i + 1][j])
			{
				i++;
				return(i);
			}
			i++;
		}
		j++;
	}
	return (i);
}



