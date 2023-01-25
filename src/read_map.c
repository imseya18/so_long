/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:44 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/25 18:31:35 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

int	ft_free(t_big *all)
{
	free(all->map);
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

int main(void)
{
	int		size;
	int		i;
	int		fd;
	t_big	all;
	int		items;

	ft_bzero(&all, sizeof(t_big));
	i = 0;
	size = read_map(open("./src/map.txt", O_RDONLY));
	if (size <= 2)
		return (ft_error("invalid map"));
	all.map = malloc((size + 1) * sizeof(char *));
	if (!all.map)
		return (ft_free(&all));
	all.map[size] = 0;
	fd = open("./src/map.txt", O_RDONLY);
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
	store_coord(&all);
	map_copy(&all, size);
	items = all.coins + all.exit;
	if (pathfinding(all.mapcpy, all.player_c.y / TSIZE, all.player_c.x / TSIZE, &items) == 0)
		return (ft_error("no path found !!!"));
}
