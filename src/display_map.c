/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:55:07 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/09 15:02:20 by mmorue           ###   ########.fr       */
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

	all->wd_calc = (WIDTH - (all->size_x * 64)) / 2;
	all->hg_calc = (HEIGHT - (all->size_y * 64)) / 2;
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
		mlx_image_to_window(all->mlx, all->img_bg[*j], size_x + all->wd_calc,
			size_y + all->hg_calc);
		size_x += 64;
		x++;
		*j += 1;
	}
}

void	display_player_coin(t_big *a)
{
	int	i;
	int	j;

	j = -1;
	while (++j < a->coins)
	{
		i = -1;
		while (++i < 4)
		{
			a->img_coin[j][i] = mlx_texture_to_image(a->mlx, a->text_coin[i]);
			mlx_image_to_window(a->mlx, a->img_coin[j][i], a->item[j].x
				+ a->wd_calc, a->item[j].y + a->hg_calc);
			if (i != 0)
				a->img_coin[j][i]->enabled = false;
		}
	}
	j = -1;
	while (++j < 16)
	{
		a->img_player[j] = mlx_texture_to_image(a->mlx, a->text_player[j]);
		mlx_image_to_window(a->mlx, a->img_player[j], a->player_c.x
			+ a->wd_calc, a->player_c.y + a->hg_calc);
		if (j != 0)
			a->img_player[j]->enabled = false;
	}
}

void	display_map_boucle(t_big *all)
{
	int	y;
	int	j;
	int	size_y;

	y = -1;
	j = 5;
	size_y = 0;
	while (all->map[++y])
	{
		display_map_in(all, &j, size_y, y);
		size_y += 64;
	}
	j = -1;
	while (++j < 5)
	{
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_camp[j]);
		mlx_image_to_window(all->mlx, all->img_bg[j], all->exit_c.x
			+ all->wd_calc, all->exit_c.y + all->hg_calc);
		if (j != 0)
			all->img_bg[j]->enabled = false;
	}
	display_player_coin(all);
}
