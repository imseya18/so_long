/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:39:57 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/08 14:29:45 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TSIZE 64
# define WIDTH 2560
# define HEIGHT 1440
# include	"../printf/ft_printf.h"
# include	"../MLX42/include/MLX42/MLX42.h"
# include	"../get_next_line/get_next_line.h"
# include <fcntl.h>
# define SP 5
# define PL 5
# define PH 20

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
	mlx_image_t		***img_coin;
	mlx_image_t		**img_player;
	mlx_texture_t	**text_player;
	mlx_texture_t	**text_bg;
	mlx_texture_t	**text_camp;
	mlx_texture_t	**text_coin;
	char			**map;
	char			**mapcpy;
	char			*line;
	t_coins			*item;
	t_coord			player_c;
	t_coord			player_c_box;
	t_coord			exit_c;
	t_coord			*wall_c;
	int				hg_calc;
	int				wd_calc;
	int				size_x;
	int				size_y;
	int				size_x_pix;
	int				size_y_pix;
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
int		store_coord_obstacle(t_big *all);
int		map_copy(t_big *all, int size);
int		pathfinding(char **tab, int y, int x, int *items);
int		fill_text(mlx_texture_t **img, int max, char *str);
int		ft_storetext(t_big *all);
void	display_corner(t_big *all, int y, int x, int j);
void	display_obstacle(t_big *all, int j);
void	display_map_in(t_big *all, int *j, int size_y, int y);
void	display_map_boucle(t_big *all);
void	display_player_coin(t_big *all);
int		hit_x(t_big *all, int pos);
int		hit_y(t_big *all, int pos);
int		check_box_down(t_big *all);
void	ft_moove_down(t_big *all);
int		check_box_up(t_big *all);
void	ft_moove_up(t_big *all);
int		check_box_left(t_big *all);
void	ft_moove_left(t_big *all);
int		check_box_right(t_big *all);
void	ft_moove_right(t_big *all);
void	ft_hook(void *param);
void	store_coord_pix(t_big *all);
#endif