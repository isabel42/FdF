/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:45:55 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/22 14:12:19 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "minilibx/mlx.h"

# include "libft/libft.h"

int main()
{
	printf("test\n");
	void *mlx_ptr;
	void *nw;
	mlx_ptr = mlx_init();
	nw = mlx_new_window(mlx_ptr, 5000, 3000, "Hello graph world");
	//return (0);
	printf("nw: %p", nw);
	}
