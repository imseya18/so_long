/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:04:08 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/31 17:18:56 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_errormap(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = ft_strlen2(str);
	write(1, "Error\n", 6);
	write(1, str, k);
	write(1, "\n", 1);
	return (0);
}

int	ft_checksizeline(char **line)
{
	int	nb;
	int	i;
	int	sizeline;

	i = 0;
	nb = 0;
	sizeline = ft_strlen(line[0]);
	while (line[nb])
	{
		if (ft_strlen(line[nb]) != sizeline)
			return (0);
		nb++;
	}
	return (1);
}

int	ft_checkwall(char **map, int size, int sizel)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (map[nb])
	{
		while (map[nb][i] && map[nb][i] != '\n')
		{
			if (map[0][i] != '1' || map [size - 1][i] != '1' )
				return (0);
			if (map[nb][0] != '1' || map[nb][sizel - 1] != '1')
				return (0);
			i++;
		}
		i = 0;
		nb++;
	}
	return (1);
}

int	ft_checkchar(char c, t_big *all)
{
	if (c != '1' && c != '0' && c != 'C'
		&& c != 'P' && c != 'E')
		return (0);
	else if (c == 'C')
		all->coins += 1;
	else if (c == 'P')
		all->player += 1;
	else if (c == 'E')
		all->exit += 1;
	return (1);
}

int	ft_checkressource(t_big *all)
{
	int	y;
	int	x;

	y = 1;
	while (all->map[y + 1])
	{
		x = 1;
		while (all->map[y][x] && all->map[y][x] != '\n')
		{
			if (ft_checkchar(all->map[y][x], all) == 0)
				return (0);
			if (y != (all->size_y - 1) && x != (all->size_x - 1)
				&& all->map[y][x] == '1')
				all->obstacle++;
			x++;
		}
		y++;
	}
	if (all->player != 1 || all->exit != 1 || all->coins == 0)
		return (0);
	return (1);
}
