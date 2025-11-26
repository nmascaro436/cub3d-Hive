/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:39:19 by nmascaro          #+#    #+#             */
/*   Updated: 2025/11/26 15:24:31 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//# include "libft/libft.h"
# include "MLX42/MLX42.h"

#define WIDTH 1920
#define HEIGHT 1080
typedef struct s_game
{
	mlx_t	*mlx;
	mlx_image_t *img;
	t_map *map; // parsing gives this
	bool forward; // is that key pressed?
	bool back;
	bool left;
	bool right;
	bool rotate_left;
	bool rotate_right;
}	t_game;

typedef struct s_player
{
	double dir_x; // direction vector
	double dir_y; // direction vector
	double plane_x; // camera plane  (perpendicular to direction and represents the "screen" or field of view)
	double plane_y; // camera plane
} t_player;


#endif