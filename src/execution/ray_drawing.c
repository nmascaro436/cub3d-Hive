/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:18:41 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/09 15:21:40 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	get_texture_column(t_ray *ray, mlx_texture_t *tex, t_player *p)
{
	double	hit_pos; // where in the horizontal or vertical line of the wall we hit
	int		tex_x;

	if (ray->dir.side == 0) //vertical side of wall
		hit_pos = p->y + ray->wall.perp_dist * ray->dir.dir_y; // x position of wall is fixed, we want to know where in y we hit (position of player + distance from player to wall * how much i move vertically)
	else // horizontal side of wall
		hit_pos = p->x + ray->wall.perp_dist * ray->dir.dir_x; // y position is fixed, we want to know where in x
	hit_pos -= (int)hit_pos; // keep only decimal part (exactly where inside that tile we hit), we dont care here in what tile we are (same texture in the whole tile, different pixels though)
	tex_x = (int)(hit_pos * tex->width); // which column of the texture does that hit correspond to
	if (tex_x < 0) // safety check for going out of bounds
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static int	get_texture_row(int y, t_ray *ray, mlx_texture_t *tex)
{
	double	tex_pos;
	int		tex_y;

	tex_pos = (double)(y - ray->wall.start_draw) / (double)ray->wall.line_height; // where in the column
	tex_y = (int)(tex_pos * tex->height); // which row of the texture 
	if (tex_y < 0) //safety check for out of bounds
		tex_y = 0;
	if (tex_y >= (int)tex->height)
		tex_y = tex->height - 1;
	return (tex_y);
}

// each pixel is 3 or 4 numbers (red, green, blue, alpha: the numbers are bytes from 0-255)
// bytes per pixel is how many numbers each pixel uses (3 or 4) -> they are stored all in tex->pixels
static int	get_texture_color(mlx_texture_t *tex, int tex_x, int tex_y)
{
	int		pixel_i;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	pixel_i = (tex_y * tex->width + tex_x) * tex->bytes_per_pixel; // WHERE THE PIXEL STARTS index of the first number of the pixel in the array = pixels above the row i want + how many pixels to the right in the current row * bytes per pixel
	r = tex->pixels[pixel_i + 0]; // assign color of red
	g = tex->pixels[pixel_i + 1]; // asign green 
	b = tex->pixels[pixel_i + 2]; // assign blue
	if (tex->bytes_per_pixel == 4)
		a = tex->pixels[pixel_i + 3]; // assign alpha (transparency) if it exists
	else
		a = 255; // opaque
	return ((r << 24) | (g << 16) | (b << 8) | a); // pack all color components into a single 32 bit int (4 bytes)
}

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
		tex_y = get_texture_row(y, ray, tex); // each row in that column
		color = get_texture_color(tex, tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}
