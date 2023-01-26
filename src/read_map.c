/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:44 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/26 17:22:15 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

int ft_storetext(t_big *all)
{
	int full_size;
	int i;

	i = 0;
	full_size = all->size_x * all->size_y;
	all->bg = malloc ((full_size) *  sizeof(mlx_image_t));
	all->img_bg = malloc(12 * sizeof(mlx_texture_t));
	while(i < 12)
	{
		all->img_bg[i] = mlx_load_png(ft_printf("sprite/%d.png", i));
		i++;
		if (!all->img_bg[i])
			return (0);
	}
	return (1);
}



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
	int		i;
	int		fd;
	t_big	all;
	int		items;

	ft_bzero(&all, sizeof(t_big));
	i = 0;
	all.size_y = read_map(open("./src/map.txt", O_RDONLY));
	if (all.size_y <= 2)
		return (ft_errormap("invalid map"));
	all.map = malloc((all.size_y + 1) * sizeof(char *));
	if (!all.map)
		return (ft_free(&all));
	all.map[all.size_y] = 0;
	fd = open("./src/map.txt", O_RDONLY);
	while (i < all.size_y)
		all.map[i++] = get_next_line(fd);   // MANQUE FONCTIONNEMENT SI ERROR DE GNL
	if (all.map[all.size_y - 1] == 0)
		return (ft_errormap("invalid map, empty line"));
	all.size_x = ft_strlen(all.map[0]);
	if (!ft_checksizeline(all.map))
		return (ft_errormap("invalid map, line not same size"));
	if (ft_checkwall(all.map, all.size_y, all.size_x) == 0)
		return (ft_errormap("invalid map, bad wall"));
	if (ft_checkressource(&all) == 0)
		return (ft_errormap("invalid map, bad ressource"));
	store_coord_coin(&all);
	store_coord_obstacle(&all);
	map_copy(&all, all.size_y);
	items = all.coins + all.exit;
	if (pathfinding(all.mapcpy, all.player_c.y / TSIZE, all.player_c.x / TSIZE, &items) == 0)
		return (ft_errormap("no path found !!!"));
	ft_storetext(&all);
}
