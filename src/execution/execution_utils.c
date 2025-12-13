/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:28:48 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/12 16:59:52 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Renders the ceiling and floor by filling the top and bottom halves of the
* screen with colors. They are drawn before the walls so that the wall rendering
* overwrites these colors.
*/
void	draw_ceil_and_floor(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height / 2)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_put_pixel(game->img, x, y, game->map->ceil_color);
			x++;
		}
		y++;
	}
	y = game->height / 2;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_put_pixel(game->img, x, y, game->map->floor_color);
			x++;
		}
		y++;
	}
}

/*
* Initializes basic ray properties for a given screen column::
* - Calculates camera_x by converting the x position to a value between
* -1 (left edge) and 1 (right edge), that represents how far the ray is from 
* the center of view.
* - Computes ray direction by combining the player's looking direction with the
* camera plane scaled by camera_x, creating the FOV effect.
* - Sets the initial map grid position of the ray to the player's current tile.
* - Calculates delta distances (distance to cross one full grid square) using ray
* direction.
*/
void	init_ray_basic(t_ray *ray, t_game *game, int x)
{
	ray->dir.camera_x = 2.0 * x / (double)game->width - 1.0;
	ray->dir.dir_x = game->player->dir_x + game->player->plane_x
		* ray->dir.camera_x;
	ray->dir.dir_y = game->player->dir_y + game->player->plane_y
		* ray->dir.camera_x;
	ray->dir.map_x = (int)game->player->x;
	ray->dir.map_y = (int)game->player->y;
	ray->dir.delta_dist_x = fabs(1 / ray->dir.dir_x);
	ray->dir.delta_dist_y = fabs(1 / ray->dir.dir_y);
	ray->dir.hit_wall = 0;
	ray->dir.side = 0;
}

/*
* Prints an error message, cleans up allocated MLX resources,
* and exits the program with failure status.
*/
void	error_and_cleanup(t_game *game, char *str)
{
	printf("Error: %s\n", str);
	if (game)
	{
		if (game->map)
		{
			if (game->map->north_tex)
				mlx_delete_texture(game->map->north_tex);
			if (game->map->south_tex)
				mlx_delete_texture(game->map->south_tex);
			if (game->map->west_tex)
				mlx_delete_texture(game->map->west_tex);
			if (game->map->east_tex)
				mlx_delete_texture(game->map->east_tex);
		}
		if (game->img && game->mlx)
			mlx_delete_image(game->mlx, game->img);
		if (game->mlx)
			mlx_terminate(game->mlx);
	}
	exit (EXIT_FAILURE);
}

/*
* Checks if the position is within the bounds of the map:
* - map_y is within the maps's height.
* - map_x is within the bounds of the current row's length.
* Returns true if valid, false otherwise.
*/
bool	is_position_valid(t_ray *ray, t_map *map)
{
	int	line_len;

	if (ray->dir.map_y < 0 || ray->dir.map_y >= map->max_y)
		return (false);
	line_len = ft_strlen(map->chart[ray->dir.map_y]);
	if (ray->dir.map_x < 0 || ray->dir.map_x >= line_len)
		return (false);
	return (true);
}

/*
* Checks if a map coordinate (x, y) is valid and within bounds
* of the map array. Similar to the is_position_valid but used for the
* movement of the player.
*/
bool    is_map_coord_safe(t_map *map, int x, int y)
{
   int line_len;


   if (y < 0 || y >= map->max_y)
       return (false);
   line_len = ft_strlen(map->chart[y]);
   if (x < 0 || x >= line_len)
       return (false); 
   return (true);
}
/*
* Called by MLX when the window is resized. Updated
* width and height, recreates the images and redraws the scene
* to match the new size.
*/
void    resize_handler(int32_t w, int32_t h, void *param)
{
   t_game *game;
  
   game = (t_game *)param;


   game->width = w;
   game->height = h;


   if (game->img)
       mlx_delete_image(game->mlx, game->img);
   game->img = mlx_new_image(game->mlx, w, h);
   mlx_image_to_window(game->mlx, game->img, 0, 0);
   draw_ceil_and_floor(game);
   raycaster(game, game->map);
}
