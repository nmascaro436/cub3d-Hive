/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:18:41 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/08 14:44:00 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t *texture_selection(t_ray *ray, t_map *map)
{
	if (ray->wall.texture == NORTH_TEXT)
		return (game->map->north_tex);
	else if (ray->wall.texture == SOUTH_TEXT)
		return (game->map->south_tex);
	else if (ray->wall.texture == EAST_TEXT)
		return(game->map->east_tex);
	else
		return(game->map->west_tex);
}

static int calculate_texture_x(t_ray *ray, mlx_texture_t *tex, t_player *p)
{
	double wall_x;
	int tex_x;

	if (ray->dir.side == 0) //vertical wall
        wall_x = player->y + ray->wall.perp_dist * ray->dir.dir_y;
    else
        wall_x = player->x + ray->wall.perp_dist * ray->dir.dir_x;
    wall_x -= (int)wall_x; 
    tex_x = (int)(wall_x * tex->width);
    if (tex_x < 0)
		tex_x = 0;
    if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
    return (tex_x);
}

static int calculate_texture_y(int y, t_ray *ray, mlx_texture_t *tex)
{
	double tex_pos;
    int tex_y;
	tex_pos = (double)(y - ray->wall.start_draw) / ray->wall.line_height;
	tex_y = (int)(tex_pos * tex->height);
    if (tex_y < 0)
		tex_y = 0;
    if (tex_y >= (int)tex->height)
		tex_y = tex->height - 1;
    return (tex_y);
}

static int get_pixel_texture(mlx_texture_t *tex, int tex_x, int tex_y)
{
    int index;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	index = (tex_y * tex->width + tex_x) * tex->bytes_per_pixel;

    r = tex->pixels[index + 0];
    g = tex->pixels[index + 1];
    b = tex->pixels[index + 2];
    if (tex->bytes_per_pixel == 4)
        a = tex->pixels[index + 3];
    else
        a = 255;
    return ((r << 24) | (g << 16) | (b << 8) | a);
}
void draw_ray(t_ray *ray, t_game *game, int x)
{
	mlx_texture_t *tex;
	int tex_x;
	int tex_y;
	int y;
	uint32_t color;

	tex = texture_selection(ray, game->map);
	tex_x = calculate_texture_x(ray, tex, game->player);
	y = ray->wall.start_draw;
	while (y <= ray->wall.end_draw)
	{
		tex_y = calculate_texture_y(y, ray, tex);
		color = get_pixel_texture(tex, tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}
