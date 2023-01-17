/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:39:57 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/17 16:58:19 by mmorue           ###   ########.fr       */
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
	int x;
	int y;
}	t_coord;

typedef struct s_big {
	char		**map;
	char		**mapcpy;
	char		*line;
	t_coins 	*item;
	t_coord 	player_c;
	t_coord		exit_c;
	int			sizel;
	int			coins;
	int			player;
	int			exit;
}	t_big;

#endif