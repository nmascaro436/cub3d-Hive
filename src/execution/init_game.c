/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:58:24 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/09 15:10:29 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_and_exit(char *str)
{
	printf("Error: %s\n", str);
	exit (EXIT_FAILURE);
}

void	error_and_cleanup(t_game *game, char *str)
{
	printf("Error: %s\n", str);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit (EXIT_FAILURE);
}

static void	init_player_execution(t_player *player)
{
	if (player->view == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66; // pointing to right side of player (so when we cast a ray it shows the screen in the correct side, not mirror)perpendicular to dir, FOV (field of view, how wide is our screen) ~66° (typical human view)
		player->plane_y = 0;
	}
	else if (player->view == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->view == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->view == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	init_game(t_game *game, t_map *map)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		error_and_exit("MLX initialization failed");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		error_and_cleanup(game, "Image creation failed");
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		error_and_cleanup(game, "Image display failed");
	game->map = map;
	game->player = map->player;
	init_player_execution(game->player);
	game->forward = false;
	game->back = false;
	game->left = false;
	game->right = false;
	game->rotate_left = false;
	game->rotate_right = false;
}
