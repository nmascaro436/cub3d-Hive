/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:18:41 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/11 11:24:34 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Selects appropriate wall texture based on the direction the ray hit the wall from.
* Returns corresponding texture pointer.
*/
static mlx_texture_t	*texture_selection(t_ray *ray, t_map *map)
{
	if (ray->wall.texture == NORTH_TEXT)
		return (map->north_tex);
	else if (ray->wall.texture == SOUTH_TEXT)
		return (map->south_tex);
	else if (ray->wall.texture == EAST_TEXT)
		return (map->east_tex);
	else
		return (map->west_tex);
}

/*
* Calculates which column of the texture should be used for this ray:
* - Determines hit position along the wall perpendicular distance (from player to wall)
* and ray direction.
* - For the vertical side of the wall, uses the y position since the x
* is fixed and for horizontal it's the opposite.
* - Extracts the decimal part to get the position inside the tile (to get the exact pixel).
* - Scales hit position to texture width to know which column of the texture the hit corresponds.
* - Performs safety checks to avoid going out of bounds.
*/
static int	get_texture_column(t_ray *ray, mlx_texture_t *tex, t_player *p)
{
	double	hit_pos;
	int		tex_x;

	if (ray->dir.side == 0)
		hit_pos = p->y + ray->wall.perp_dist * ray->dir.dir_y;
	else
		hit_pos = p->x + ray->wall.perp_dist * ray->dir.dir_x;
	hit_pos -= (int)hit_pos;
	tex_x = (int)(hit_pos * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

/*
* Calculates which row of the texture corresponds to the pixel being drawn:
* - Determines position within the column, comparing current y with the 
*	start position of the texture and the line height of the wall.
* - Scales it to the texture height to get the row oof the texture.
* - Performs safety checks to avoid going out of bounds.
*/
static int	get_texture_row(int y, t_ray *ray, mlx_texture_t *tex)
{
	double	tex_pos;
	int		tex_y;

	tex_pos = (double)(y - ray->wall.start_draw) / (double)ray->wall.line_height;
	tex_y = (int)(tex_pos * tex->height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)tex->height)
		tex_y = tex->height - 1;
	return (tex_y);
}

/*
* Extracts the color value from a texture at the specified coordinates.
* Textures store pixel data as arrays of bytes, each pixel is (3 or 4 bytes).
* Calculates the byte index where this pixel's color data starts (skips all rows
* above, moves right within the current row to find pixel position and multiplies
* by bytes per pixel to convert from pixel index to byte index in the 1D array).
* Extracts red, green, blue and alpha (transparency) components and puts them into
* a single 32 bit int in RGBA format using bit shifting.
*/
static int	get_texture_color(mlx_texture_t *tex, int tex_x, int tex_y)
{
	int		pixel_i;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	pixel_i = (tex_y * tex->width + tex_x) * tex->bytes_per_pixel;
	r = tex->pixels[pixel_i + 0];
	g = tex->pixels[pixel_i + 1];
	b = tex->pixels[pixel_i + 2];
	if (tex->bytes_per_pixel == 4)
		a = tex->pixels[pixel_i + 3];
	else
		a = 255;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/*
* Called once per screen column (x coordinate) during raycasting loop.
* Draws one vertical column of pixels on the screen representing the wall seen 
* by this ray:
* - Selects texture.
* - Calculates which column to use based on hit position.
* - For each pixel on that column, determines texture row, retrieves color and renders.
*/
void	draw_ray(t_ray *ray, t_game *game, int x)
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				tex_y;
	int				y;
	uint32_t		color;

	tex = texture_selection(ray, game->map);
	tex_x = get_texture_column(ray, tex, game->player);
	y = ray->wall.start_draw;
	while (y <= ray->wall.end_draw)
	{
		tex_y = get_texture_row(y, ray, tex);
		color = get_texture_color(tex, tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}
