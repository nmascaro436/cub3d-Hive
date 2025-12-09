/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:39:19 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/09 15:31:02 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080
# define NORTH_TEXT 1
# define SOUTH_TEXT 2
# define WEST_TEXT 3
# define EAST_TEXT 4

typedef struct s_player
{
	double	x;
	double	y;
	char	view;
	double	dir_x; // direction vector
	double	dir_y; // direction vector
	double	plane_x; // camera plane  (perpendicular to direction and represents the "screen" or field of view)
	double	plane_y; // camera plane
}	t_player;

typedef struct s_map
{
	int				max_x;
	int				max_y;
	int				floor_color;
	int				ceil_color;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*east_tex;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	bool		forward;
	bool		back;
	bool		left;
	bool		right;
	bool		rotate_left;
	bool		rotate_right;
}	t_game;

typedef struct s_ray_dir
{
	double	camera_x; // horizontal position of the ray on the camera plane
	double	dir_x; // direction vector of the ray
	double	dir_y; // direction vector of the ray
	int		map_x; // current grid cell the ray is in
	int		map_y; // current grid cell the ray is in
	double	side_dist_x; // distance from current position to next x side (vertical wall line)
	double	side_dist_y; // distance from current position to next y side (horizontal wall line)
	double	delta_dist_x; // distance needed to cross one full square in x
	double	delta_dist_y; // distance needed to cross one full square in y
	int		step_x; // +1 (right) or -1 (left)
	int		step_y; // +1 (down) -1 (up)
	int		hit_wall; // did i hit a wall?
	int		side; // which side of a wall was hit? 0 = vertical (x side)wall 1 = horizontal wall (y side)
}	t_ray_dir;
typedef struct s_ray_wall
{
	double	perp_dist; // perpendicular distance to wall (distance from player to wall in the direction player is looking, like real forward distance, so walls aren't curved)
	int		line_height; // height of wall 
	int		start_draw; // y coordinate to start draw
	int		end_draw; // y coordinate to stop draw
	int		texture; // wall texture
}	t_ray_wall;
typedef struct s_ray
{
	t_ray_dir	dir;
	t_ray_wall	wall;
}	t_ray;

t_game	*parse(char **argv);
void	init_game(t_game *game, t_map *map);
void	error_and_cleanup(t_game *game, char *str);
void	error_and_exit(char *str);
void	setup_run_game(t_game *game, t_map *map);
void	raycaster(t_game *game, t_map *map);
void	draw_ray(t_ray *ray, t_game *game, int x);
void	move_player(t_game *game, t_map *map);

#endif