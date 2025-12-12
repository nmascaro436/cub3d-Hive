/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:39:19 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/12 14:24:23 by jkorvenp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>

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
	char			**chart;
	int				max_x;
	int				max_y;
	int				start_line;
	t_player		*player;
	uint32_t		floor_color;
	uint32_t		ceil_color;
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

void	init_game_exec(t_game *game, t_map *map);
void	error_and_cleanup(t_game *game, char *str);
void	setup_run_game(t_game *game, t_map *map);
void	raycaster(t_game *game, t_map *map);
void	draw_ray(t_ray *ray, t_game *game, int x);
void	move_player(t_game *game);
void	draw_ceil_and_floor(t_game *game);
void	init_ray_basic(t_ray *ray, t_game *game, int x);
bool	is_position_valid(t_ray *ray, t_map *map);

//parse.c
t_game	*parse(char *argv);
bool	parse_map(t_game *game, t_map *map, char *argv);
bool	parse_textures(t_game *game, t_map *map, char *argv);

//map.c
bool	validate_map(t_game *game, t_map *map, char **chart);

//textures.c
bool	check_textures(t_map *map, char *line);

//utils.c
void    free_all(t_game *game);
void	free_chart(t_map *map, int y);
bool    valid_file(char *argv, char *file, int len);
bool	empty_line(char *line);
int		check_state(t_map *map);
void	print_map(t_map *map);
void	print_player(t_player *player);
void	print_textures(t_map *map);

#endif