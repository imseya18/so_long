/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:39:57 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/30 14:15:12 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BPP sizeof(int32_t)
# define TSIZE 64
#define WIDTH 1920
#define HEIGHT 1080
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
	mlx_t			*mlx;
	mlx_image_t		**img_bg;
	mlx_image_t		**img_coin;
	mlx_image_t		**img_player;
	mlx_texture_t 	**text_player;
	mlx_texture_t 	**text_bg;
	mlx_texture_t 	**text_camp;
	mlx_texture_t 	**text_coin;
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
int		ft_free_exit(t_big *all);
int		checkline(char *buffer);
int		read_map(int fd);
void	store_coord_pe(t_big *all);
int		store_coord_coin(t_big *all);
int 	store_coord_obstacle(t_big *all);
int		map_copy(t_big *all, int size);
int		pathfinding(char **tab, int y, int x, int *items);
int 	fill_text(mlx_texture_t **img, int max, char *str);
int 	ft_storetext(t_big *all);

#endif