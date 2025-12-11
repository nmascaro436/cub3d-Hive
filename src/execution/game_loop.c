/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:47:38 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/11 14:40:16 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Key handler helper. Handles key press by setting the flags to true.
* WASD control movement, arrow keys control camera rotation,
* and ESC exits the game.
*/
static void	key_press_handler(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		error_and_cleanup(game, "Game closed");
	else if (keydata.key == MLX_KEY_W)
		game->forward = true;
	else if (keydata.key == MLX_KEY_S)
		game->back = true;
	else if (keydata.key == MLX_KEY_A)
		game->left = true;
	else if (keydata.key == MLX_KEY_D)
		game->right = true;
	else if (keydata.key == MLX_KEY_LEFT)
		game->rotate_left = true;
	else if (keydata.key == MLX_KEY_RIGHT)
		game->rotate_right = true;
}

/*
* Main keyboard input handler. Calls key_press_handler and sets
* the flags back to false when the keys are released.
*/
static void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
		key_press_handler(keydata, game);
	else if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
			game->forward = false;
		else if (keydata.key == MLX_KEY_S)
			game->back = false;
		else if (keydata.key == MLX_KEY_A)
			game->left = false;
		else if (keydata.key == MLX_KEY_D)
			game->right = false;
		else if (keydata.key == MLX_KEY_LEFT)
			game->rotate_left = false;
		else if (keydata.key == MLX_KEY_RIGHT)
			game->rotate_right = false;
	}
}

/*
* Loads N, S, E, W wall textures from png files.
* If they fail to load, game exits and cleans up resources.
*/
static void	load_textures(t_game *game)
{
	game->map->north_tex = mlx_load_png(game->map->north);
	if (!game->map->north_tex)
		error_and_cleanup(game, "Failed to load texture");
	game->map->south_tex = mlx_load_png(game->map->south);
	if (!game->map->south_tex)
		error_and_cleanup(game, "Failed to load texture");
	game->map->west_tex = mlx_load_png(game->map->west);
	if (!game->map->west_tex)
		error_and_cleanup(game, "Failed to load texture");
	game->map->east_tex = mlx_load_png(game->map->east);
	if (!game->map->east_tex)
		error_and_cleanup(game, "Failed to load texture");
}

/*
* Game loop that runs every frame. Does the following steps:
* - Updates player's position and rotation based on pressed keys.
* - Renders the scene by drawing the ceiling and floor.
* - Performs raycasting loop to render the walls.
*/
static void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	move_player(game);
	draw_ceil_and_floor(game);
	raycaster(game, game->map);
}

/*
* Entry point for the execution of the game. Initializes game structure
* and MLX window, loads wall textures, runs the game loop and sets up
* key handler. Loop runs until the window is closed or ESC is pressed.
*/
void	setup_run_game(t_game *game, t_map *map)
{
	init_game_exec(game, map);
	load_textures(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, key_handler, game);
	mlx_loop(game->mlx);
}
