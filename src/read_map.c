/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:44 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/30 17:24:15 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
void display_corner(t_big *all, int y, int x, int j)
{
	if (y == 0 && x == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[0]);
	else if (y == 0 && x == all->size_x - 1)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[1]);
	else if (y == all->size_y - 1 && x == all->size_x - 1)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[2]);
	else if(y == all->size_y - 1 && x == 0)
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
void display_obstacle(t_big *all, int j)
{
	if(j % 3 == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[9]);
	else if(j % 5 == 0)
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[10]);
	else
		all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[11]);
}	
void	display_map(t_big *all)
{
	int	x;
	int	y;
	int	j;
	int size_x;
	int size_y;

	y = -1;
	j = 0;
	size_y = 0;
	while (all->map[++y])
	{
		x = 0;
		size_x = 0;
		while (all->map[y][x] && all->map[y][x] != '\n')
		{
			if (all->map[y][x] == '1' && (y == 0  || x == 0 || y == all->size_y - 1 || x == all->size_x - 1))
				display_corner(all, y, x, j);
			else if (all->map[y][x] == '1')
				display_obstacle(all, j);
			else
				all->img_bg[j] = mlx_texture_to_image(all->mlx, all->text_bg[8]);
			mlx_image_to_window(all->mlx, all->img_bg[j], size_x, size_y);
			size_x += 64;
			x++;
			j++;
		}
		size_y += 64;
	}
}

int ft_storetext(t_big *all)
{
	int full_size;
	int i;

	i = 0;
	full_size = all->size_x * all->size_y;
	all->img_bg = malloc ((full_size + 4) *  sizeof(mlx_image_t));
	all->img_coin = malloc(4 * sizeof(mlx_image_t));
	all->img_player = malloc(16 * sizeof(mlx_image_t));
	all->text_bg = malloc(12 * sizeof(mlx_texture_t));
	all->text_camp = malloc(5 * sizeof(mlx_texture_t));
	all->text_coin = malloc(4 * sizeof(mlx_texture_t));
	all->text_player = malloc(16 * sizeof(mlx_image_t));

	fill_text(all->text_bg, 12, "sprite/bg/");
	fill_text(all->text_camp, 5,"sprite/campfire/campfire");
	fill_text(all->text_coin, 4,"sprite/coin/coin");
	fill_text(all->text_player, 16, "sprite/player/player");
	return (1);
}
int fill_text(mlx_texture_t **img, int max, char *str)
{
	int i;

	i = 0;

	while(i < max)
	{
		img[i] = mlx_load_png(ft_printf("%s%d.png",str,i)); 
		if (!img[i])		 		//crée fonction qui free avec le memory manager + exit.
			return (0); 
		i++;
	}
	return(1);
}

int	ft_free_exit(t_big *all)
{
	free(all->map);
	return(0);
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
		return (ft_free_exit(&all));
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
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	ft_storetext(&all);
	//all.img_bg[0] = mlx_texture_to_image(all.mlx, all.text_player[15]);
	//mlx_image_to_window(all.mlx, all.img_bg[0], 0, 0);
	display_map(&all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
 	return (EXIT_SUCCESS);
}
