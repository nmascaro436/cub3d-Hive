/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:28:48 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/10 10:11:07 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil_and_floor(t_game *game)
{
	int	x;
	int	y;

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

void	init_ray_basic(t_ray *ray, t_game *game, int x)
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
}

void	error_and_exit(char *str)
{
	printf("Error: %s\n", str);
	exit (EXIT_FAILURE);
}

void	error_and_cleanup(t_game *game, char *str)
{
	printf("Error: %s\n", str);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit (EXIT_FAILURE);
}
