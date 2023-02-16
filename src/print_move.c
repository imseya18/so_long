/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:31:04 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/16 15:50:15 by mmorue           ###   ########.fr       */
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

int	check_ber(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 1] != 'r' || str[i - 2] != 'e' || str[i - 3] != 'b'
		|| str[i - 4] != '.')
		return (ft_errormap("map isn't .ber"));
	return (1);
}

void	print_move(t_big *all)
{
	if (all->temp_time < mlx_get_time() * 1000)
	{
		all->temp_time = mlx_get_time() * 1000 + 50;
		if (all->temp_player_c.x != all->player_c_box.x
			|| all->temp_player_c.y != all->player_c_box.y)
		{
			all->movement += 1;
			write(1, ft_printf("MOVES: %d\n", all->movement),
				ft_strlen(ft_printf("MOVES: %d\n", all->movement)));
			all->temp_player_c.x = all->player_c_box.x;
			all->temp_player_c.y = all->player_c_box.y;
		}
	}	
}
