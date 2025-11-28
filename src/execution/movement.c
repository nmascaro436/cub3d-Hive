/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:55:45 by nmascaro          #+#    #+#             */
/*   Updated: 2025/11/28 10:13:56 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// to avoid moving inside the wall grid cell, so i dont accidentally go to far into a wall before
// collision check stops me
// it allows sliding against walls naturally
static void move_try(t_game *game, t_map *map, double new_x, double new_y) // tell Jenni to add a grid or some tiles (2d array of  map)
{
	if (map->grid[(int)game->player->y][(int)new_x] != '1') // If I stay at my current row (Y), and move to the new column (X), is there a wall?
		game->player->x = new_x; // move right
	if (map->grid[(int)new_y][(int)game->player->x] != '1') // If I stay at my current column (X), and move to the new row (Y), is there a wall?
		game->player->y = new_y; // move up
}

static void handle_movement(t_game *game, t_map *map, double move_speed)
{
	double new_x;
	double new_y;

	if (game->forward)
	{
		new_x = game->player->x + game->player->dir_x * move_speed; // move that much in the specified direction
		new_y = game->player->y + game->player->dir_y * move_speed;
		move_try(game, map, new_x, new_y);
	}
	if (game->back)
	{
		new_x = game->player->x - game->player->dir_x * move_speed;
		new_y = game->player->y - game->player->dir_y * move_speed;
		move_try(game, map, new_x, new_y);
	}
	if (game->left)
	{
		new_x = game->player->x - game->player->plane_x * move_speed; // plane always points to right, so - plane means left (its like sidestepping)
		new_y = game->player->y - game->player->plane_y * move_speed;
		move_try(game, map, new_x, new_y);
	}	
	if (game->right)
	{
		new_x = game->player->x + game->player->plane_x * move_speed;
		new_y = game->player->y + game->player->plane_y * move_speed;
		move_try(game, map, new_x, new_y);
	}
}
//When angle = 0° → cos = 1 (fully right), sin = 0 (not up/down)
//When angle = 90° → cos = 0, sin = 1 (fully up)
//When angle = 180° → cos = -1, sin = 0 (fully left)
//When angle = 270° → cos = 0, sin = -1 (fully down)

static void rotate_calculation(double *x, double *y, double angle)
{
	double old_x;
	double cos_a;
	double sin_a;

	old_x = *x; // save old x because we will overwrite it
	cos_a = cos(angle); // how far to the side i am (horizontal part of that direction)
	sin_a = sin(angle); // how far up/down i am (vertical part of that direction)
	*x = old_x * cos_a - *y * sin_a;
	*y = old_x * sin_a - *y * cos_a;
}

static void handle_rotation(t_game *game, double rotation_speed)
{
	if (game->rotate_left)
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

void move_player(t_game *game, t_map *map)
{
	double move_speed;
	double rotation_speed;

	move_speed = 0.05; // smooth value so the movement is natural (in terms of a grid square: which is 1)
	rotation_speed = 0.03; // smooth value so the rotation is natural (in terms of radians per frame: 1 radian == 57 degrees)
	handle_movement(game, map, move_speed);
	handle_rotation(game, rotation_speed);
}
