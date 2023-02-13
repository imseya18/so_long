/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:04:09 by mmorue            #+#    #+#             */
/*   Updated: 2023/02/02 15:49:50 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "so_long.h"
//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <memory.h>
//#define WIDTH 1920
//#define HEIGHT 1080

//static void ft_error(void)
//{
//	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
//	exit(EXIT_FAILURE);
//}
//
//static void ft_hook(void* param)
//{
//	const mlx_t*	mlx	= param;
//
//	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
//}


//int	main(void)
//{
//	mlx_t	*test;
//
//	test = mlx_init(1920, 1080, "coucou", false);
//	if (!test)
//		ft_error();
//	mlx_image_t	*img = mlx_new_image(test, 64, 64);
//	ft_memset(img->pixels, 255, img->width * img->height * BPP);
//	if (!img || (mlx_image_to_window(test, img, 64, 0) < 0))
//		ft_error();
//	mlx_loop_hook(test, ft_hook, test);
//	mlx_loop(test);
//	mlx_terminate(test);
//	return (EXIT_SUCCESS);
//}
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <memory.h>
//#define WIDTH 1920
//#define HEIGHT 1080
//
//mlx_image_t	*g_img;
//
//void	hook(void *param)
//{
//	mlx_t	*mlx;
//
//	mlx = param;
//	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
//		mlx_close_window(mlx);
//	if (mlx_is_key_down(mlx, MLX_KEY_W))
//		g_img->instances[0].y -= 10;
//	if (mlx_is_key_down(mlx, MLX_KEY_S))
//		g_img->instances[0].y += 10;
//	if (mlx_is_key_down(mlx, MLX_KEY_A))
//		g_img->instances[0].x -= 10;
//	if (mlx_is_key_down(mlx, MLX_KEY_D))
//		g_img->instances[0].x += 10;
//}
//
//int32_t	main(void)
//{
//	mlx_t	*mlx;
//
//	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
//	if (!mlx)
//		exit(EXIT_FAILURE);
//	g_img = mlx_new_image(mlx, 64, 1228);
//	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
//	mlx_image_to_window(mlx, g_img, 0, 0);
//	mlx_loop_hook(mlx, &hook, mlx);
//	mlx_loop(mlx);
//	mlx_terminate(mlx);
//	return (EXIT_SUCCESS);
//}

