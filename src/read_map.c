/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:44 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/17 16:44:22 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_free_exit(void)
{
	ftm_free_all();
	exit(0);
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

int	test_map(t_big *all, char *str)
{
	int	i;
	int	fd;

	i = 0;
	all->size_y = read_map(ftm_open(str, O_RDONLY));
	if (all->size_y <= 2)
		return (ft_errormap("invalid map"));
	all->map = ftm_malloc((all->size_y + 1) * sizeof(char *));
	if (!all->map)
		return (ft_free_exit());
	all->map[all->size_y] = 0;
	fd = ftm_open(str, O_RDONLY);
	while (i < all->size_y)
		all->map[i++] = get_next_line(fd);
	ftm_close(fd);
	if (all->map[all->size_y - 1] == 0)
		return (ft_errormap("invalid map, empty line"));
	all->size_x = ft_strlen_n(all->map[0]);
	if (!ft_checksizeline(all->map))
		return (ft_errormap("invalid map, line not same size"));
	if (ft_checkwall(all->map, all->size_y, all->size_x) == 0)
		return (ft_errormap("invalid map, bad wall"));
	if (ft_checkressource(all) == 0)
		return (ft_errormap("invalid map, bad ressource"));
	return (1);
}

int	main(int argc, char **argv)
{
	t_big	all;
	int		items;

	if (argc != 2)
		return (0);
	ft_bzero(&all, sizeof(t_big));
	if (check_ber(argv[1]) == 0)
		return (0);
	if (test_map(&all, argv[1]) == 0)
		return (0);
	store_coord_coin(&all);
	store_coord_obstacle(&all);
	map_copy(&all, all.size_y);
	items = all.coins + all.exit;
	if (pathfinding(all.mapcpy, all.player_c.y / TSIZE,
			all.player_c.x / TSIZE, &items) == 0)
		return (ft_errormap("no path found !!!"));
	store_coord_pix(&all);
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	ft_storetext(&all);
	display_map_boucle(&all);
	mlx_loop_hook(all.mlx, ft_hook, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	return (EXIT_SUCCESS);
}
