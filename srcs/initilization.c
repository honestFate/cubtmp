/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 07:44:07 by gtrinida          #+#    #+#             */
/*   Updated: 2022/11/01 02:59:49 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initilization(t_mlx *mlx, char *line)
{
	//сделать функцию которая будет искать место спавна на карте, возможнно
	//это делает парсер, нужно будет спросить у Славы
	mlx->info->pos_x = 0;
	mlx->info->pos_y = 0;
	mlx->info->dir_x = -1;
	mlx->info->dir_y = 0;
	mlx->info->plane_x = 0;
	mlx->info->plane_y = 0.66;
	mlx->info->color = 0xe0ffff;
	mlx->mlx_ptr = mlx_init();
	mlx->info->move_speed = 0.3;
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, screenWidth, screenHeight, "Raycaster");
	mlx->img = mlx_new_image(mlx->mlx_ptr, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
		&mlx->line_length, &mlx->endian);
	mlx->map_path = ft_strdup(line);
	//ниже нужно создать отдельную функцию которая будет переделывать отдельные текстуры
}
