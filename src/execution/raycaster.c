/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:46:52 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/03 16:32:02 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void init_ray(t_ray *ray, t_game *game, int x)
{
	ray->dir.camera_x = 2.0 * x / (double)WIDTH - 1.0; //converts pixel position to a num between -1 and 1 (we know were the ray is pointing at, "percentage" of how far left/right i am looking)
	ray->dir.dir_x = game->player->dir_x + game->player->plane_x * ray->dir.camera_x; // where i am looking + peripheral vision * how far left/right ray is from center
	ray->dir.dir_y = game->player->dir_y + game->player->plane_y * ray->dir.camera_x;
	ray->dir.map_x = (int)game->player->x; // where ray is (specific grid)
	ray->dir.map_y = (int)game->player->y;
	ray->dir.delta_dist_x = fabs(1 / ray->dir.dir_x); // fabs is floating point absolute value(means it makes negative numbers positive) and 1 because we want to know distance to cross 1 grid square
	ray->dir.delta_dist_y = fabs(1 / ray->dir.dir_y);
	ray->dir.hit_wall = 0;
	ray->dir.side = 0;
	if (ray->dir.dir_x < 0)
	{
		ray->dir.step_x = -1; // go left
		ray->dir.side_dist_x = (game->player->x - ray->dir.map_x ) * ray->dir.delta_dist_x;
	}
	else
	{
		ray->dir.step_x = 1; // go right
		ray->dir.side_dist_x = (ray->dir.map_x + 1.0 - game->player->x) * ray->dir.delta_dist_x; // square we're in + 1(next vertical line) - exact position  = distance to that line * delta_dist to convert to ray distance
	}
	if (ray->dir.dir_y < 0)
	{
		ray->dir.step_y = -1; // go up
		ray->dir.side_dist_y = (game->player->y - ray->dir.map_y ) * ray->dir.delta_dist_y;
	}
	else
	{
		ray->dir.step_y = 1; // go down
		ray->dir.side_dist_y = (ray->dir.map_y + 1.0 - game->player->y) * ray->dir.delta_dist_y;
	}
}

void	dda_logic(t_ray *ray, t_map *map)
{
	while (ray->dir.hit_wall == '0')
	{
		if (ray->dir.side_dist_x < ray->dir.side_dist_y) // move in x
		{
			ray->dir.side_dist_x += ray->dir.delta_dist_x;
			ray->dir.map_x += ray->dir.step_x;
			ray->dir.side = 0;
		}
		else // move in y
		{
			ray->dir.side_dist_y += ray->dir.delta_dist_y;
			ray->dir.map_y += ray->dir.step_y;
			ray->dir.side = 1;	
		}
		if(map->map[ray->dir.map_y][ray.dir.map_x] == '1')
			ray->dir.hit_wall = 1;
	}
}
/*
*1. Compute perpendicular wall distance

The formula depends on whether the hit side was vertical or horizontal.

2. Compute line height

Use perpendicular distance to find wall height on screen.

3. Compute drawing start and end Y positions

Center the wall vertically.

4. Clamp start and end to window bounds

Make sure they do not go outside the screen.
*/
void	calculate_wall(t_ray *ray, t_map *map)
{

}

// DDA traces a ray step by step through the map and checks each step if i've hit a wall, stops when i do
// and records the distance
///each ray is a vertical stripe of pixels on the screen
void raycaster(t_game *game, t_map *map)
{
	int x;
	t_ray ray;

	x = 0;
	while (x < WIDTH) //  loop through every vertical stripe (x pixel) on the screen
	{
		init_ray(&ray, game, x);
		dda_logic(&ray, map);
		calculate_wall(&ray);
		draw_ray(&ray, game);
		x++;
	}
}
