/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:47:38 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/01 14:24:11 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void key_handler(mlx_key_data_t keydata, void *param)
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

int game_loop(void * param)
{
	t_game *game;

	game = (t_game *)param;
	move_player(game, game->map);
	raycaster(game, game->map);
	return (0);
}
void setup_run_game(t_game *game, t_map *map)
{
	init_game(game, map);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, key_handler, game);
	mlx_loop(game->mlx);
}
