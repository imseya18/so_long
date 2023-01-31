/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:55:07 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/31 17:18:53 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_corner(t_big *all, int y, int x, int j)
{
	if (y == 0 && x == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[0]);
	else if (y == 0 && x == all->size_x - 1)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[1]);
	else if (y == all->size_y - 1 && x == all->size_x - 1)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[2]);
	else if (y == all->size_y - 1 && x == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[3]);
	else if (y == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[5]);
	else if (y == all->size_y - 1)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[4]);
	else if (x == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[6]);
	else if (x == all->size_x - 1)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[7]);
}

void	display_obstacle(t_big *all, int j)
{
	if (j % 3 == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[9]);
	else if (j % 5 == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[10]);
	else
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[11]);
}

void	display_map_in(t_big *all, int *j, int size_y, int y)
{
	int	x;
	int	size_x;
	int	wd_calc;
	int	hg_calc;

	wd_calc = (WIDTH - (all->size_x * 64)) / 2;
	hg_calc = (HEIGHT - (all->size_y * 64)) / 2;
	x = 0;
	size_x = 0;
	while (all->map[y][x] && all->map[y][x] != '\n')
	{	
		if (all->map[y][x] == '1' && (y == 0 || x == 0
			|| y == all->size_y - 1 || x == all->size_x - 1))
			display_corner(all, y, x, *j);
		else if (all->map[y][x] == '1')
			display_obstacle(all, *j);
		else
			all->img_bg[*j] = mlx_texture_to_image(all->mlx, all->text_bg[8]);
		mlx_image_to_window(all->mlx, all->img_bg[*j], size_x + wd_calc,
			size_y + hg_calc);
		size_x += 64;
		x++;
		*j += 1;
	}
}

void	display_map_boucle(t_big *all)
{
	int	y;
	int	j;
	int	size_y;

	y = -1;
	j = 0;
	size_y = 0;
	while (all->map[++y])
	{
		display_map_in(all, &j, size_y, y);
		size_y += 64;
	}
}
