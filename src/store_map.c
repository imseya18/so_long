/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:02:13 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/31 17:19:25 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	store_coord_obstacle(t_big *all)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	all->wall_c = malloc(all->obstacle * sizeof(t_coord));
	if (!all->wall_c)
		return (ft_free_exit(all));
	while (all->map[++y + 1])
	{
		x = 1;
		while (x < all->size_x - 1)
		{
			if (all->map[y][x] == '1' )
			{
				all->wall_c[i].y = y * TSIZE;
				all->wall_c[i].x = x * TSIZE;
				i++;
			}
			x++;
		}
	}
	return (1);
}

void	store_coord_pe(t_big *all)
{
	int	y;
	int	x;

	y = 1;
	x = 0;
	while (all->map[y + 1])
	{
		while (all->map[y][x] && all->map[y][x] != '\n')
		{
			if (all->map[y][x] == 'P')
			{
				all->player_c.y = y * TSIZE;
				all->player_c.x = x * TSIZE;
			}
			if (all->map[y][x] == 'E')
			{
				all->exit_c.y = y * TSIZE;
				all->exit_c.x = x * TSIZE;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

int	store_coord_coin(t_big *all)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	all->item = malloc(all->coins * sizeof(t_coins));
	if (!all->item)
		return (ft_free_exit(all));
	while (all->map[++y + 1])
	{
		x = 0;
		while (all->map[y][x] && all->map[y][x] != '\n')
		{
			if (all->map[y][x] == 'C')
			{
				all->item[i].y = y * TSIZE;
				all->item[i].x = x * TSIZE;
				i++;
			}
			x++;
		}
	}
	store_coord_pe(all);
	return (1);
}

int	map_copy(t_big *all, int size)
{
	int	y;

	y = 0;
	all->mapcpy = malloc((size + 1) * sizeof(char *));
	if (!all->mapcpy)
		return (ft_free_exit(all));  		// faire les FREE.
	all->mapcpy[size] = 0;
	while (all->map[y])
	{
		all->mapcpy[y] = ft_strdup(all->map[y]);
		if (!all->mapcpy[y])
			return (ft_free_exit(all));
		y++;
	}
	return (1);
}

int	pathfinding(char **tab, int y, int x, int *items)
{
	if (tab[y][x] == '1')
		return (0);
	if (tab[y][x] == 'C' || tab[y][x] == 'E')
		*items -= 1;
	tab[y][x] = '1';
	pathfinding(tab, y - 1, x, items);
	pathfinding(tab, y + 1, x, items);
	pathfinding(tab, y, x - 1, items);
	pathfinding(tab, y, x + 1, items);
	if (*items == 0)
		return (1);
	return (0);
}
