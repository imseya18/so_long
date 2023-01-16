/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:44 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/16 18:13:53 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

int	ft_free(t_big *all)
{
	free(all->map);
	return (0);
}

int	ft_error(char *str)
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

int	checkline(char *buffer)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			size++;
		i++;
	}
	return (size);
}

int	read_map(int fd)
{
	char	buffer[2];
	int		size;

	buffer[1] = '\0';
	size = 1;
	if (read(fd, 0, 0) < 0 || fd < 0)
		return (1);
	while (read(fd, buffer, 1) > 0)
		size += checkline(buffer);
	close(fd);
	return (size);
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

int ft_checksizeline(char **line)
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

int ft_checkchar(char c, t_big *all)
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

int ft_checkressource(t_big *all)
{
	int	y;
	int	x;

	y = 1;
	x = 0;
	while (all->map[y + 1])
	{
		while (all->map[y][x] && all->map[y][x] != '\n')
		{
			if (ft_checkchar(all->map[y][x], all) == 0)
				return (0);
			x++;
		}
		x = 0;
		y++;
	}
	if (all->player != 1 || all->exit != 1 || all->coins == 0)
		return (0);
	return (1);
}
void storecoord(t_big *all)
{
	int y;
	int x;
	int i;

	i = 0;
	y = 1;
	x = 0;
	all->item = malloc(all->coins * sizeof(t_coins));
	while (all->map[y + 1])
	{
		while (all->map[y][x] && all->map[y][x] != '\n')
		{
			if (all->map[y][x] == 'C')
			{
				all->item[i].x = y;
				all->item[i].x = x;
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
int main(void)
{
	int		size;
	int		i;
	int		fd;
	t_big	all;

	ft_bzero(&all, sizeof(t_big));
	i = 0;
	size = read_map(open("./map.txt", O_RDONLY));
	if (size <= 2)
		return (ft_error("invalid map"));
	all.map = malloc((size + 1) * sizeof(char *));
	if (!all.map)
		return (ft_free(&all));
	all.map[size] = 0;
	fd = open("./map.txt", O_RDONLY);
	while (i < size)
		all.map[i++] = get_next_line(fd);   // MANQUE FONCTIONNEMENT SI ERROR DE GNL
	if (all.map[size - 1] == 0)
		return (ft_error("invalid map, empty line"));
	all.sizel = ft_strlen(all.map[0]);
	if (!ft_checksizeline(all.map))
		return (ft_error("invalid map, line not same size"));
	if (ft_checkwall(all.map, size, all.sizel) == 0)
		return (ft_error("invalid map, bad wall"));
	if (ft_checkressource(&all) == 0)
		return (ft_error("invalid map, bad ressource"));
		
	
}
