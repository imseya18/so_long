/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:58:37 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/09 15:02:23 by mmorue           ###   ########.fr       */
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

void	ft_hook(void *param)
{
	t_big	*all;
	int		i;

	i = 0;
	all = param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(all->mlx);
	if (mlx_is_key_down(all->mlx, MLX_KEY_W))
		ft_moove_up(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		ft_moove_down(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		ft_moove_left(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		ft_moove_right(all);
	display_exit(all);
}

void	store_coord_pix(t_big *all)
{
	int	i;

	i = -1;
	all->player_c_box.x = all->player_c.x;
	all->player_c_box.y = all->player_c.y;
	all->size_x_pix = all->size_x * 64;
	all->size_y_pix = all->size_y * 64;
	all->coins_check = all->coins;
	while (++i < all->coins)
		all->item[i].on_map = 0;
}
