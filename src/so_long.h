/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:39:57 by mmorue            #+#    #+#             */
/*   Updated: 2023/01/11 15:41:08 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#define BPP sizeof(int32_t)

#include	"../printf/ft_printf.h"
#include	"../MLX42/include/MLX42/MLX42.h"
#include	"../get_next_line/get_next_line.h"

typedef struct s_big {
	char **map;
	char *line;
	int	 sizel;
} t_big;

#endif