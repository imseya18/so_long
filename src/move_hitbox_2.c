/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hitbox_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:26:14 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/17 16:44:18 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_box_left(t_big *all)
{
	int	i;

	i = -1;
	if (all->player_c_box.x - SP < 64)
	{
		return (hit_x(all, 64));
	}
	i = -1;
	while (++i < all->obstacle)
	{
		if (all->player_c_box.x + 64 - SP - PL > all->wall_c[i].x + 32 + PL
			&& all->player_c_box.x - SP < all->wall_c[i].x + 64 - PL
			&& all->player_c_box.y - 64 + PH < all->wall_c[i].y
			&& all->player_c_box.y > all->wall_c[i].y - 64 + PL)
		{
			return (hit_x(all, all->wall_c[i].x + 64 - SP));
		}
	}
	return (1);
}

void	ft_moove_left(t_big *all)
{
	int	i;

	i = 0;
	if (check_box_left(all) == 1)
	{
		all->img_player[8]->enabled = true;
		all->player_c_box.x -= SP;
		while (i < 16)
		{
			all->img_player[i]->instances[0].x -= SP;
			if (i != 8)
				all->img_player[i]->enabled = false;
			i++;
		}
	}
	check_box_coin_left(all);
}

int	check_box_right(t_big *all)
{
	int	i;

	i = -1;
	if (all->player_c_box.x + 64 + SP > all->size_x_pix - 64)
	{
		return (hit_x(all, all->size_x_pix - 128));
	}
	i = -1;
	while (++i < all->obstacle)
	{
		if (all->player_c_box.x + 64 - PL + SP > all->wall_c[i].x - PL
			&& all->player_c_box.x + SP < all->wall_c[i].x + 32 + PL
			&& all->player_c_box.y - 64 + PH < all->wall_c[i].y
			&& all->player_c_box.y > all->wall_c[i].y - 64 + PL)
		{
			return (hit_x(all, all->wall_c[i].x - 64 + SP));
		}
	}
	return (1);
}

void	ft_moove_right(t_big *all)
{
	int	i;

	i = 0;
	if (check_box_right(all) == 1)
	{
		all->img_player[12]->enabled = true;
		all->player_c_box.x += SP;
		while (i < 16)
		{
			all->img_player[i]->instances[0].x += SP;
			if (i != 12)
				all->img_player[i]->enabled = false;
			i++;
		}
	}
	check_box_coin_right(all);
}

int	hit_x(t_big *all, int pos)
{
	int	i;

	i = -1;
	all->player_c_box.x = pos;
	while (++i < 16)
		all->img_player[i]->instances[0].x = all->player_c_box.x + all->wd_calc;
	return (0);
}
