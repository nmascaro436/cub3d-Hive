/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:46:52 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/17 10:14:23 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Initializes the stepping direction and initial side distances for the ray.
* Step direction determines if we move left/right or up/down.
* Side distance is how far the ray has to travel to reach next vertical
* or horizontal grid line;
* - For negative directions, the next grid line is the left/top edge of
* the current tile.
* - For positive directions, the next grid line is the right/bottom edge of
* the current tile.
* - Multiplies by delta_dist to convert from grid units to actual ray distance.
*/
static void	init_ray_steps(t_ray *ray, t_game *game)
{
	if (ray->dir.dir_x < 0)
	{
		ray->dir.step_x = -1;
		ray->dir.side_dist_x = (game->player->x - ray->dir.map_x)
			* ray->dir.delta_dist_x;
	}
	else
	{
		ray->dir.step_x = 1;
		ray->dir.side_dist_x = (ray->dir.map_x + 1.0 - game->player->x)
			* ray->dir.delta_dist_x;
	}
	if (ray->dir.dir_y < 0)
	{
		ray->dir.step_y = -1;
		ray->dir.side_dist_y = (game->player->y - ray->dir.map_y)
			* ray->dir.delta_dist_y;
	}
	else
	{
		ray->dir.step_y = 1;
		ray->dir.side_dist_y = (ray->dir.map_y + 1.0 - game->player->y)
			* ray->dir.delta_dist_y;
	}
}

/*
* Checks if the ray has hit a wall at the current grid position and
* determines which texture to use based on the side of the wall hit.
* Before accessing the array, checks if the position is out of bounds,
* if it is, marks it as hitting a wall and returns.
* Sets the hit_wall flag to 1 when a wall is found in the map.
*/
static void	dda_check_hit(t_ray *ray, t_map *map)
{
	if (!is_position_valid(ray, map))
	{
		ray->dir.hit_wall = 1;
		ray->wall.texture = NORTH_TEXT;
		return ;
	}
	if (map->chart[ray->dir.map_y][ray->dir.map_x] == '1')
	{
		ray->dir.hit_wall = 1;
		if (ray->dir.side == 0)
		{
			if (ray->dir.step_x == 1)
				ray->wall.texture = WEST_TEXT;
			else
				ray->wall.texture = EAST_TEXT;
		}
		else
		{
			if (ray->dir.step_y == 1)
				ray->wall.texture = NORTH_TEXT;
			else
				ray->wall.texture = SOUTH_TEXT;
		}
	}
}

/*
* Implements the main DDA algorithm logic to trace the ray through the grid.
* At each step, compares horizontal and vertical side distances to determine
* which one is closer so the ray will cross it. When moving horizontally,
* increments side_dist_x and map_x. When moving vertically, same for y.
* Continues stepping until a wall is hit.
*/
static void	dda_logic(t_ray *ray, t_map *map)
{
	while (ray->dir.hit_wall == 0)
	{
		if (ray->dir.side_dist_x < ray->dir.side_dist_y)
		{
			ray->dir.side_dist_x += ray->dir.delta_dist_x;
			ray->dir.map_x += ray->dir.step_x;
			ray->dir.side = 0;
		}
		else
		{
			ray->dir.side_dist_y += ray->dir.delta_dist_y;
			ray->dir.map_y += ray->dir.step_y;
			ray->dir.side = 1;
		}
		dda_check_hit(ray, map);
	}
}

/*
* Calculates the perpendicular distance from player to wall and determines
* the wall's dimensions in the screen:
* - After DDA, side_dist contains the full distance traveled, we substract
* delta_dist to get distance to the actual line (not the full grid square).
* - Wall height is inversely proportional to distance
* (small distance = bigger wall).
* Centers the wall vertically on screen by calculating start/end draw positions.
*/
static void	calculate_wall(t_ray *ray, t_game *game)
{
	if (ray->dir.side == 0)
		ray->wall.perp_dist = ray->dir.side_dist_x - ray->dir.delta_dist_x;
	else
		ray->wall.perp_dist = ray->dir.side_dist_y - ray->dir.delta_dist_y;
	ray->wall.line_height = game->height / ray->wall.perp_dist;
	ray->wall.start_draw = (game->height / 2) - (ray->wall.line_height / 2);
	ray->wall.end_draw = (game->height / 2) + (ray->wall.line_height / 2);
}

/*
* Main raycasting function that renders the 3D view.
* Casts one ray per screen column (x) from left to right across the 
* screen width. Does all the necessary steps to create
* the illusion of the map being 3D.
*/
void	raycaster(t_game *game, t_map *map)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < game->width)
	{
		init_ray_basic(&ray, game, x);
		init_ray_steps(&ray, game);
		dda_logic(&ray, map);
		calculate_wall(&ray, game);
		draw_ray(&ray, game, x);
		x++;
	}
}
