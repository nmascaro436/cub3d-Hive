/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:55:45 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/16 14:21:03 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Attempts to move the player in a specified direction by calculating 
* the new position based on direction vector and movement speed.
* Allows the player to slide against the walls naturally instead of 
* moving inside the wall grid cell and getting stuck. 
* Checks first horizontal movement (keeping y constant) and
* then vertical movement (keeping x constant).
*/
static void	move_try(t_game *game, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;
	int		check_x;
	int		check_y;

	new_x = game->player->x + dir_x * speed;
	new_y = game->player->y + dir_y * speed;
	check_x = (int)new_x;
	check_y = (int)game->player->y;
	if (is_map_coord_safe(game->map, check_x, check_y))
	{
		if (game->map->chart[check_y][check_x] != '1')
			game->player->x = new_x;
	}
	check_x = (int)game->player->x;
	check_y = (int)new_y;
	if (is_map_coord_safe(game->map, check_x, check_y))
	{
		if (game->map->chart[check_y][check_x] != '1')
			game->player->y = new_y;
	}
}

/*
* Handles player movement based on pressed movement keys:
* - W/S keys move forward/backward along the direction vector.
* - A/D keys move  left/right perpendicular to the direction using
* the plane vector (plane vector always points to the right of the
* dir vector, negating it means moving left).
*/
static void	handle_movement(t_game *game, double move_speed)
{
	if (game->forward)
		move_try(game, game->player->dir_x, game->player->dir_y, move_speed);
	if (game->back)
		move_try(game, -game->player->dir_x, -game->player->dir_y, move_speed);
	if (game->left)
	{
		move_try(game, -game->player->plane_x, -game->player->plane_y,
			move_speed);
	}
	if (game->right)
	{
		move_try(game, game->player->plane_x, game->player->plane_y,
			move_speed);
	}
}

/*
* Performs the rotation on a vector by the specified angle using the matrix
* rotation formula. Saves old x value before overwriting (new x and y depend 
* on the original x). cos(angle) is how much of the vector stays in its original
* direction and sin(angle) is how much of it moves into the perpendicular
* direction.
*/
static void	rotate_calculation(double *x, double *y, double angle)
{
	double	old_x;
	double	cos_a;
	double	sin_a;

	old_x = *x;
	cos_a = cos(angle);
	sin_a = sin(angle);
	*x = old_x * cos_a - *y * sin_a;
	*y = old_x * sin_a + *y * cos_a;
}

/*
* Handles camera rotation based on arrow key input. Rotates both
* the direction vector (where the player is looking) and the 
* plane vector (field of view). Both need to rotate together to keep
* the FOV perpendicular. Left arrow rotates counter-clockwise
* (positive angle), right arrow rotates clockwise (negative angle).
*/
static void	handle_rotation(t_game *game, double rotation_speed)
{
	if (game->rotate_left)
	{
		rotate_calculation(&game->player->dir_x,
			&game->player->dir_y, rotation_speed);
		rotate_calculation(&game->player->plane_x,
			&game->player->plane_y, rotation_speed);
	}
	if (game->rotate_right)
	{
		rotate_calculation(&game->player->dir_x,
			&game->player->dir_y, -rotation_speed);
		rotate_calculation(&game->player->plane_x,
			&game->player->plane_y, -rotation_speed);
	}
}

/*
* Main player movement update called every frame. Sets movement speed (based on
* units per frame, 1 unit = 1 grid square) and rotation speed (based on radians
* per frame, 1 radian ~= 57 degrees) to values that provide smooth
* and natural feeling.
*/
void	move_player(t_game *game)
{
	double	move_speed;
	double	rotation_speed;

	move_speed = 0.05;
	rotation_speed = 0.03;
	handle_movement(game, move_speed);
	handle_rotation(game, rotation_speed);
}
