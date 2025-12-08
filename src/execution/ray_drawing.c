/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:18:41 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/08 12:19:04 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void draw_ray(t_ray *ray, t_game *game)
{
	int y;
	char *texture;

	if (ray->wall.texture == NORTH_TEXT)
		texture = game->map->north;
	else if (ray->wall.texture == SOUTH_TEXT)
		texture = game->map->south;
	else if (ray->wall.texture == EAST_TEXT)
		texture = game->map->east;
	else
		texture = game->map->west;
	y = ray->wall.start_draw;
	while (y <= ray->wall.end_draw)
	{
		y++;
	}
}