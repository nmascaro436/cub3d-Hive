/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:55:45 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/10 09:58:50 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// to avoid moving inside the wall grid cell, so i dont accidentally go to far into a wall
// it allows sliding against walls naturally
static void	move_try(t_game *game, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x + dir_x * speed; // // move that much in the specified direction
	new_y = game->player->y + dir_y * speed;
	if (game->map->chart[(int)game->player->y][(int)new_x] != '1') // If I stay at my current row (Y), and move to the new column (X), is there a wall?
		game->player->x = new_x; // if  not wall move horizontally
	if (game->map->chart[(int)new_y][(int)game->player->x] != '1') // If I stay at my current column (X), and move to the new row (Y), is there a wall?
		game->player->y = new_y; // if not wall move vertically
}

static void	handle_movement(t_game *game, double move_speed)
{
	if (game->forward)
		move_try(game, game->player->dir_x, game->player->dir_y, move_speed);
	if (game->back)
		move_try(game, -game->player->dir_x, -game->player->dir_y, move_speed);
	if (game->left)
	{
		move_try(game, -game->player->plane_x, -game->player->plane_y,
			move_speed); //plane always points to right, so - plane means left (its like sidestepping)
	}
	if (game->right)
	{
		move_try(game, game->player->plane_x, game->player->plane_y,
			move_speed);
	}
}

static void	rotate_calculation(double *x, double *y, double angle)
{
	double	old_x;
	double	cos_a;
	double	sin_a;

	old_x = *x; // save old x because we will overwrite it
	cos_a = cos(angle); // how much of the rotation is "horizontal"
	sin_a = sin(angle); // how much of the rotation is "vertical"
	*x = old_x * cos_a - *y * sin_a; // take some of the old sideways position and take some of the old up/down position
	*y = old_x * sin_a + *y * cos_a;
}

static void	handle_rotation(t_game *game, double rotation_speed)
{
	if (game->rotate_left) // need to rotate both direction (where i look) and the plane (field of view)
	{
		rotate_calculation(&game->player->dir_x, &game->player->dir_y, rotation_speed);
		rotate_calculation(&game->player->plane_x, &game->player->plane_y, rotation_speed);
	}
	if (game->rotate_right)
	{
		rotate_calculation(&game->player->dir_x, &game->player->dir_y, -rotation_speed);
		rotate_calculation(&game->player->plane_x, &game->player->plane_y, -rotation_speed);
	}
}

void	move_player(t_game *game, t_map *map)
{
	double	move_speed;
	double	rotation_speed;

	move_speed = 0.05; // smooth value so the movement is natural (in terms of a grid square: which is 1)
	rotation_speed = 0.03; // smooth value so the rotation is natural (in terms of radians per frame: 1 radian == 57 degrees)
	handle_movement(game, map, move_speed);
	handle_rotation(game, rotation_speed);
}
