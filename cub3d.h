/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:39:19 by nmascaro          #+#    #+#             */
/*   Updated: 2025/11/26 15:50:58 by nmascaro         ###   ########.fr       */
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

#define WIDTH 1920
#define HEIGHT 1080
typedef struct s_player
{
	double	x;
	double	y;
	char	view;
	double dir_x; // direction vector
	double dir_y; // direction vector
	double plane_x; // camera plane  (perpendicular to direction and represents the "screen" or field of view)
	double plane_y; // camera plane
}	t_player;

typedef struct map
{
	int		max_x;
	int		max_y;
	int		*floor_color;
	int		*ceil_color;
	char	*north;
	char 	*south;
	char	*west;
	char 	*east;
}  t_map;

typedef struct game
{
	t_map		*map;
	t_player	*player;
	mlx_t	*mlx;
	mlx_image_t *img;
	bool forward; // is that key pressed?
	bool back;
	bool left;
	bool right;
	bool rotate_left;
	bool rotate_right;
}	t_game;

t_game	*parse(char **argv);

#endif