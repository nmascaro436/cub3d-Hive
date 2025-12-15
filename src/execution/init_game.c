/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:58:24 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/15 16:46:28 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Initializes player direction and camera plane for N and S orientations:
* - N faces up with camera plane pointing right.
* - S faces down with camera plane pointing "left"
* (it's right when facing south).
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
* - Sets up player's initial direction and camera plane based 
* on spawn orientation.
* - Initializes movement and rotation flags to false.
* If there's any error, game cleans up and exits.
*/
void	init_game_exec(t_game *game, t_map *map)
{
	game->width = WIDTH;
	game->height = HEIGHT;
	game->mlx = mlx_init(game->width, game->height, "cub3D", true);
	if (!game->mlx)
		error_and_cleanup(game, "MLX initialization failed");
	game->img = mlx_new_image(game->mlx, game->width, game->height);
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

/*
* Initializes basic ray properties for a given screen column::
* - Calculates camera_x by converting the x position to a value between
* -1 (left edge) and 1 (right edge), that represents how far the ray is from 
* the center of view.
* - Computes ray direction by combining the player's looking direction with the
* camera plane scaled by camera_x, creating the FOV effect.
* - Sets the initial map grid position of the ray to the player's current tile.
* - Calculates delta distances (distance to cross one full grid square) using ray
* direction.
*/
void	init_ray_basic(t_ray *ray, t_game *game, int x)
{
	ray->dir.camera_x = 2.0 * x / (double)game->width - 1.0;
	ray->dir.dir_x = game->player->dir_x + game->player->plane_x
		* ray->dir.camera_x;
	ray->dir.dir_y = game->player->dir_y + game->player->plane_y
		* ray->dir.camera_x;
	ray->dir.map_x = (int)game->player->x;
	ray->dir.map_y = (int)game->player->y;
	ray->dir.delta_dist_x = fabs(1 / ray->dir.dir_x);
	ray->dir.delta_dist_y = fabs(1 / ray->dir.dir_y);
	ray->dir.hit_wall = 0;
	ray->dir.side = 0;
}

void	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	error_and_cleanup(game, "Window closed");
	free_chart(game->map->chart, game->map->max_y);
	free_all(game);
	exit (EXIT_SUCCESS);
}
