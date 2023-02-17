/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hitbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:23:53 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/17 16:44:20 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_box_down(t_big *all)
{
	int	i;

	i = -1;
	if (all->player_c_box.y + 64 + SP > all->size_y_pix - 64)
	{
		return (hit_y(all, all->size_y_pix - 128));
	}
	i = -1;
	while (++i < all->obstacle)
	{
		if (all->player_c_box.y + 64 - PH + SP > all->wall_c[i].y - PH
			&& all->player_c_box.y + SP < all->wall_c[i].y - 32 + PH
			&& all->player_c_box.x - 64 + PL < all->wall_c[i].x
			&& all->player_c_box.x > all->wall_c[i].x - 64 + PH)
		{
			return (hit_y(all, all->wall_c[i].y - 64 + SP));
		}
	}
	return (1);
}

void	ft_moove_down(t_big *all)
{
	int	i;

	i = 0;
	if (check_box_down(all) == 1)
	{
		all->img_player[0]->enabled = true;
		all->player_c_box.y += SP;
		while (i < 16)
		{
			all->img_player[i]->instances[0].y += SP;
			if (i != 0)
				all->img_player[i]->enabled = false;
			i++;
		}
	}
	check_box_coin_down(all);
}

int	check_box_up(t_big *all)
{
	int	i;

	i = -1;
	if (all->player_c_box.y - SP < 32)
	{
		return (hit_y(all, 32));
	}
	i = -1;
	while (++i < all->obstacle)
	{
		if (all->player_c_box.y + 64 - SP - PH > all->wall_c[i].y + 32 + PH
			&& all->player_c_box.y - SP < all->wall_c[i].y + 64 - PH
			&& all->player_c_box.x - 64 + PL < all->wall_c[i].x
			&& all->player_c_box.x > all->wall_c[i].x - 64 + PH)
		{
			return (hit_y(all, all->wall_c[i].y + 64 - PH));
		}
	}
	return (1);
}

void	ft_moove_up(t_big *all)
{
	int	i;

	i = 0;
	if (check_box_up(all) == 1)
	{
		all->img_player[4]->enabled = true;
		all->player_c_box.y -= SP;
		while (i < 16)
		{
			all->img_player[i]->instances[0].y -= SP;
			if (i != 4)
				all->img_player[i]->enabled = false;
			i++;
		}
	}
	check_box_coin_up(all);
}

int	hit_y(t_big *all, int pos)
{
	int	i;

	i = -1;
	all->player_c_box.y = pos;
	while (++i < 16)
		all->img_player[i]->instances[0].y = all->player_c_box.y + all->hg_calc;
	return (0);
}
