/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:58:24 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/11 14:35:36 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Initializes player direction and camera plane for N and S orientations:
* - N faces up with camera plane pointing right.
* - S faces down with camera plane pointing "left" (it's right when facing south).
* Plane value creates a typical human view FOV, plane has to be perpendicular
* to direction to ensure rendering without distortion.
*/
static void	init_player_north_south(t_player *player)
{
	if (player->view == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->view == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

/*
* Initializes player direction and camera plane for E and W orientations:
* - E faces right with camera plane pointing down.
* - W faces left with camera plane pointing up.
*/
static void	init_player_east_west(t_player *player)
{
	if (player->view == 'E')
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

/*
* Initializes game structure and MLX system:
* - Creates window with the specified dimensions.
* - Allocates main rendering image and displays it.
* - Sets up player's initial direction and camera plane based on spawn orientation.
* - Initializes movement and rotation flags to false.
* If there's any error, game cleans up and exits.
*/
void	init_game_exec(t_game *game, t_map *map)
{
	printf("Before mlx_init\n");
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		error_and_cleanup(game, "MLX initialization failed");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		error_and_cleanup(game, "Image creation failed");
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		error_and_cleanup(game, "Image display failed");
	game->map = map;
	game->player = map->player;
	init_player_north_south(game->player);
	init_player_east_west(game->player);
	game->forward = false;
	game->back = false;
	game->left = false;
	game->right = false;
	game->rotate_left = false;
	game->rotate_right = false;
}
