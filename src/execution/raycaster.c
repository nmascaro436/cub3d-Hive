/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:46:52 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/01 14:38:06 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"








// DDA traces a ray step by step through the map and checks each step if i've hit a wall, stops when i do
// and records the distance
void raycaster(t_game *game, t_map *map)
{
	int x;
	t_ray *ray;

	x = 0;
	while (x < WIDTH) //  loop through every vertical stripe (x pixel) on the screen
	{
		init_ray();
		dda_logic();
		calculate_wall();
		draw_ray();
		x++;
	}
}