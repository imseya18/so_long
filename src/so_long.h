/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:39:57 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/26 17:22:31 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BPP sizeof(int32_t)
# define TSIZE 64
#include	"../printf/ft_printf.h"
#include	"../MLX42/include/MLX42/MLX42.h"
#include	"../get_next_line/get_next_line.h"

typedef struct s_coin {
	int	x;
	int	y;
}	t_coins;

typedef struct s_coord{
	int	x;
	int	y;
}	t_coord;

typedef struct s_big {
	mlx_image_t		**bg;
	mlx_texture_t 	**img_bg;
	char			**map;
	char			**mapcpy;
	char			*line;
	t_coins			*item;
	t_coord			player_c;
	t_coord			exit_c;
	t_coord			*wall_c;
	int				size_x;
	int 			size_y;
	int				obstacle;
	int				coins;
	int				player;
	int				exit;
}	t_big;

int		ft_errormap(char *str);
int		ft_checksizeline(char **line);
int		ft_checkwall(char **map, int size, int sizel);
int		ft_checkchar(char c, t_big *all);
int		ft_checkressource(t_big *all);
int		ft_free(t_big *all);
int		checkline(char *buffer);
int		read_map(int fd);
void	store_coord_pe(t_big *all);
int		store_coord_coin(t_big *all);
int 	store_coord_obstacle(t_big *all);
int		map_copy(t_big *all, int size);
int		pathfinding(char **tab, int y, int x, int *items);

#endif