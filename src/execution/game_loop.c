/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:47:38 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/08 14:49:18 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void key_handler(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
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

static void draw_ceil_and_floor(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->map->ceil_color);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->map->floor_color);
			x++;
		}
		y++;
	}
}
static void load_textures(t_game *game)
{
	game->map->north_tex = mlx_load_png(game->map->north); //changee validation in parsiiiiing!!!! not xpm
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

static int game_loop(void * param)
{
	t_game *game;

	game = (t_game *)param;
	move_player(game, game->map);
	draw_ceil_and_floor(game);
	raycaster(game, game->map);
	return (0);
}
void setup_run_game(t_game *game, t_map *map)
{
	init_game(game, map);
	load_textures(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, key_handler, game);
	mlx_loop(game->mlx);
}
