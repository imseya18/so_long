/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_hitbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:52:58 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/16 15:50:21 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_succes(void)
{
	write(1, "GOOD JOB! You beat the game\n", 28);
	ftm_free_all();
	exit(0);
}

int	check_box_exit_down(t_big *all)
{
	if (all->player_c_box.y + 64 - PH + SP > all->exit_c.y - PH
		&& all->player_c_box.y + SP < all->exit_c.y - 32 + PH
		&& all->player_c_box.x - 64 + PL < all->exit_c.x
		&& all->player_c_box.x > all ->exit_c.x - 64 + PH)
	{
		exit_succes();
	}
	return (0);
}

int	check_box_exit_up(t_big *all)
{
	if (all->player_c_box.y + 64 - SP - PH > all->exit_c.y + 32 + PH
		&& all->player_c_box.y - SP < all->exit_c.y + 64 - PH
		&& all->player_c_box.x - 64 + PL < all->exit_c.x
		&& all->player_c_box.x > all->exit_c.x - 64 + PH)
	{
		exit_succes();
	}
	return (0);
}

int	check_box_exit_left(t_big *all)
{
	if (all->player_c_box.x + 64 - SP - PL > all->exit_c.x + 32 + PL
		&& all->player_c_box.x - SP < all->exit_c.x + 64 - PL
		&& all->player_c_box.y - 64 + PH < all->exit_c.y
		&& all->player_c_box.y > all ->exit_c.y - 64 + PL)
	{
		exit_succes();
	}
	return (0);
}

int	check_box_exit_right(t_big *all)
{
	if (all->player_c_box.x + 64 - PL + SP > all->exit_c.x - PL
		&& all->player_c_box.x + SP < all->exit_c.x + 32 + PL
		&& all->player_c_box.y - 64 + PH < all->exit_c.y
		&& all->player_c_box.y > all->exit_c.y - 64 + PL)
	{
		exit_succes();
	}
	return (0);
}
