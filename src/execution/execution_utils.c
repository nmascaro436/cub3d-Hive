/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:28:48 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/15 11:05:29 by nmascaro         ###   ########.fr       */
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
