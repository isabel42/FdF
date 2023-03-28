/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:09:38 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/28 19:31:11 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// size_t	ft_strlen( char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t	len_s1;
// 	size_t	len_s2;
// 	char	*sol;
// 	size_t	i;

// 	len_s1 = ft_strlen(s1);
// 	len_s2 = ft_strlen(s2);
// 	i = 0;
// 	sol = malloc((len_s1 + len_s2 + 1) * sizeof(*s1));
// 	if (!sol)
// 		return (NULL);
// 	while (i < len_s1)
// 	{
// 		sol[i] = s1[i];
// 		s1[i] = '\0';
// 		i++;
// 	}
// 	while (i < len_s1 + len_s2)
// 	{
// 		sol[i] = s2[i - len_s1];
// 		i++;
// 	}
// 	ft_free(s1);
// 	sol [i] = '\0';
// 	return (sol);
// }

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
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
