/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_hitbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:11:19 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/09 15:02:17 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_exit(t_big *all)
{
	int	i;

	i = -1;
	if (all->coins_check == 0)
	{
		while (++i < 5)
		{
			all->img_bg[i]->enabled = false;
			if (i == 2)
				all->img_bg[i]->enabled = true;
		}
		check_box_exit_down(all);
		check_box_exit_up(all);
		check_box_exit_left(all);
		check_box_exit_right(all);
	}
}

int	check_box_coin_down(t_big *all)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while (++i < all->coins)
	{
		if (all->player_c_box.y + 64 - PH + SP > all->item[i].y - PH
			&& all->player_c_box.y + SP < all->item[i].y - 32 + PH
			&& all->player_c_box.x - 64 + PL < all->item[i].x
			&& all->player_c_box.x > all ->item[i].x - 64 + PH
			&& all->item[i].on_map == 0)
		{
			all->coins_check--;
			all->item[i].on_map = 1;
			while (++j < 4)
				all->img_coin[i][j]->enabled = false;
			return (1);
		}
	}
	return (0);
}

int	check_box_coin_up(t_big *all)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while (++i < all->coins)
	{
		if (all->player_c_box.y + 64 - SP - PH > all->item[i].y + 32 + PH
			&& all->player_c_box.y - SP < all->item[i].y + 64 - PH
			&& all->player_c_box.x - 64 + PL < all->item[i].x
			&& all->player_c_box.x > all->item[i].x - 64 + PH
			&& all->item[i].on_map == 0)
		{
			all->coins_check--;
			all->item[i].on_map = 1;
			while (++j < 4)
				all->img_coin[i][j]->enabled = false;
			return (1);
		}
	}
	return (0);
}

int	check_box_coin_left(t_big *all)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while (++i < all->coins)
	{
		if (all->player_c_box.x + 64 - SP - PL > all->item[i].x + 32 + PL
			&& all->player_c_box.x - SP < all->item[i].x + 64 - PL
			&& all->player_c_box.y - 64 + PH < all->item[i].y
			&& all->player_c_box.y > all ->item[i].y - 64 + PL
			&& all->item[i].on_map == 0)
		{
			all->coins_check--;
			all->item[i].on_map = 1;
			while (++j < 4)
				all->img_coin[i][j]->enabled = false;
			return (1);
		}
	}
	return (0);
}

int	check_box_coin_right(t_big *all)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while (++i < all->coins)
	{
		if (all->player_c_box.x + 64 - PL + SP > all->item[i].x - PL
			&& all->player_c_box.x + SP < all->item[i].x + 32 + PL
			&& all->player_c_box.y - 64 + PH < all->item[i].y
			&& all->player_c_box.y > all->item[i].y - 64 + PL
			&& all->item[i].on_map == 0)
		{
			all->coins_check--;
			all->item[i].on_map = 1;
			while (++j < 4)
				all->img_coin[i][j]->enabled = false;
			return (1);
		}
	}
	return (0);
}
