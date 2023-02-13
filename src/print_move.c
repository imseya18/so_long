/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:31:04 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/13 16:01:44 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_n(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

void	print_move(t_big *all)
{
	if(all->temp_time < mlx_get_time() * 1000)
	{
		all->temp_time = mlx_get_time() * 1000 + 50;
		if (all->temp_player_c.x != all->player_c_box.x
			|| all->temp_player_c.y != all->player_c_box.y)
		{
			all->movement += 1;
			//printf("%d\n", all->movement);
			write(1, ft_printf("MOVES: %d\n", all->movement), ft_strlen(ft_printf("MOVES: %d\n", all->movement)));
			all->temp_player_c.x = all->player_c_box.x;
			all->temp_player_c.y = all->player_c_box.y;
		}
	}	
}
