/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:44 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/02 18:07:38 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_storetext(t_big *all)
{
	int	full_size;
	int	i;

	i = -1;
	full_size = all->size_x * all->size_y;
	all->img_bg = malloc ((full_size + 4) * sizeof(mlx_image_t));
	all->img_coin = malloc((all->coins) * sizeof(mlx_image_t *));
	while (++i < all->coins)
		all->img_coin[i] = malloc(4 * sizeof(mlx_image_t));
	all->img_player = malloc(16 * sizeof(mlx_image_t));
	all->text_bg = malloc(12 * sizeof(mlx_texture_t));
	all->text_camp = malloc(5 * sizeof(mlx_texture_t));
	all->text_coin = malloc(4 * sizeof(mlx_texture_t));
	all->text_player = malloc(16 * sizeof(mlx_image_t));
	fill_text(all->text_bg, 12, "sprite/bg/");
	fill_text(all->text_camp, 5, "sprite/campfire/campfire");
	fill_text(all->text_coin, 4, "sprite/coin/coin");
	fill_text(all->text_player, 16, "sprite/player/player");
	return (1);
}

int	fill_text(mlx_texture_t **img, int max, char *str)
{
	int	i;

	i = 0;
	while (i < max)
	{
		img[i] = mlx_load_png(ft_printf("%s%d.png", str, i));
		if (!img[i])		 		//crée fonction qui free avec le memory manager + exit.
			return (0);
		i++;
	}
	return (1);
}

int	ft_free_exit(t_big *all)
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

int test_map(t_big *all)
{
	int	i;
	int	fd;

	i = 0;
	all->size_y = read_map(open("./src/map.txt", O_RDONLY));
	if (all->size_y <= 2)
		return (ft_errormap("invalid map"));
	all->map = malloc((all->size_y + 1) * sizeof(char *));
	if (!all->map)
		return (ft_free_exit(all));
	all->map[all->size_y] = 0;
	fd = open("./src/map.txt", O_RDONLY);
	while (i < all->size_y)
		all->map[i++] = get_next_line(fd);   // MANQUE FONCTIONNEMENT SI ERROR DE GNL
	if (all->map[all->size_y - 1] == 0)
		return (ft_errormap("invalid map, empty line"));
	all->size_x = ft_strlen(all->map[0]);
	if (!ft_checksizeline(all->map))
		return (ft_errormap("invalid map, line not same size"));
	if (ft_checkwall(all->map, all->size_y, all->size_x) == 0)
		return (ft_errormap("invalid map, bad wall"));
	if (ft_checkressource(all) == 0)
		return (ft_errormap("invalid map, bad ressource"));
	return (1);
}
void ft_moove_down(t_big *all)
{
	int i;

	i = 0;
	all->img_player[0]->enabled = true;
	all->player_c_box.y += 5;
	while(i < 16)
	{
		all->img_player[i]->instances[0].y += 5;
		if(i != 0)
			all->img_player[i]->enabled = false;
		i++;
	}
}

int check_box_up(t_big *all)
{
	int i;

	i = -1;
	if(all->player_c_box.y - 5 < 64)
	{
		return(hit_y(all, 64));
	}
	i = -1;
	while(++i < all->obstacle)
	{
		if(all->player_c_box.x + 64 > all->wall_c[i].x
		&& all->player_c_box.x  < all->wall_c[i].x + 64
		&& all->player_c_box.y - 59 < all->wall_c[i].y
		&& all->player_c_box.y - 5 > all->wall_c[i].y - 64)
		{
			hit_y(all, all->wall_c[i].y + 64);
		}
	}
	return(1);
}

void ft_moove_up(t_big *all)
{
	int i;

	i = 0;
	all->img_player[4]->enabled = true;
	if(check_box_up(all) == 1)
	{
		all->player_c_box.y -= 5;
		while(i < 16)
		{
			all->img_player[i]->instances[0].y -= 5;
			if(i != 4)
				all->img_player[i]->enabled = false;
			i++;
		}
	}
}

int check_box_left(t_big *all)
{
	int i;

	i = -1;
	if(all->player_c_box.x - 5 < 64)
	{
		return(hit_x(all, 64));
	}
	i = -1;
	while(++i < all->obstacle)
	{
		if(all->player_c_box.x + 59 > all->wall_c[i].x
		&& all->player_c_box.x - 5 < all->wall_c[i].x + 64
		&& all->player_c_box.y - 64 < all->wall_c[i].y
		&& all->player_c_box.y > all ->wall_c[i].y - 64)
		{
			hit_x(all, all->wall_c[i].x + 64);
		}
	}
	return(1);
}

void ft_moove_left(t_big *all)
{
	int i;

	i = 0;
	all->img_player[8]->enabled = true;
	if(check_box_left(all) == 1)
	{
		all->player_c_box.x -= 5;
		while(i < 16)
		{
			all->img_player[i]->instances[0].x -= 5;
			if(i != 8)
				all->img_player[i]->enabled = false;
			i++;
		}
	}
}
int hit_x(t_big *all, int pos)
{
	int i;

	i = -1;
	all->player_c_box.x = pos;
	while(++i < 16)
		all->img_player[i]->instances[0].x = all->player_c_box.x + all->wd_calc;
	return(0);
}

int hit_y(t_big *all, int pos)
{
	int i;

	i = -1;
	all->player_c_box.y = pos;
	while(++i < 16)
		all->img_player[i]->instances[0].y = all->player_c_box.y + all->hg_calc;
	return(0);
}
int check_box_right(t_big *all)
{
	int i;

	i = -1;
	if(all->player_c_box.x + 69 > all->size_x_pix - 64)
	{
		return(hit_x(all, all->size_x_pix - 128));
	}
	i = -1;
	while(++i < all->obstacle)
	{
		if(all->player_c_box.x + 69 > all->wall_c[i].x
		&& all->player_c_box.x + 5 < all->wall_c[i].x + 64
		&& all->player_c_box.y - 64 < all->wall_c[i].y
		&& all->player_c_box.y > all ->wall_c[i].y - 64)
		{
			hit_x(all, all->wall_c[i].x - 64);
		}
	}
	return(1);
}

void ft_moove_right(t_big *all)
{
	int i;

	i = 0;
	all->img_player[12]->enabled = true;
	if(check_box_right(all) == 1)
	{
		all->player_c_box.x += 5;
		while(i < 16)
		{
			all->img_player[i]->instances[0].x += 5;
			if(i != 12)
				all->img_player[i]->enabled = false;
			i++;
		}
	}
}

void ft_hook(void *param)
{
	t_big *all;
	int i;

	i = 0;
	all = param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
	if (mlx_is_key_down(all->mlx, MLX_KEY_UP))
		ft_moove_up(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_DOWN))
		ft_moove_down(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		ft_moove_left(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		ft_moove_right(all);
}
void store_coord_pix(t_big *all)
{
	all->player_c_box.x = all->player_c.x;
	all->player_c_box.y = all->player_c.y;
	all->size_x_pix = all->size_x * 64;
	all->size_y_pix = all->size_y * 64;
}
int main(void)
{
	t_big	all;
	int		items;

	ft_bzero(&all, sizeof(t_big));
	test_map(&all);
	store_coord_coin(&all);
	store_coord_obstacle(&all);
	map_copy(&all, all.size_y);
	items = all.coins + all.exit;
	all.player_c_box.x = all.player_c.x;
	all.player_c_box.y = all.player_c.y;
	if (pathfinding(all.mapcpy, all.player_c.y / TSIZE,
			all.player_c.x / TSIZE, &items) == 0)
		return (ft_errormap("no path found !!!"));
	int i = -1;
	while(++i < all.obstacle)
	{
		printf("---y = %d---\n---x = %d---\n", all.wall_c[i].y,all.wall_c[i].x);
	}
	store_coord_pix(&all);
	all.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	ft_storetext(&all);
	display_map_boucle(&all);
	mlx_loop_hook(all.mlx, ft_hook, &all);
	mlx_loop(all.mlx);
	mlx_terminate(all.mlx);
	return (EXIT_SUCCESS);
}
