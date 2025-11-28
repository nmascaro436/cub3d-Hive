/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:39:19 by nmascaro          #+#    #+#             */
/*   Updated: 2025/11/27 13:44:57 by jkorvenp         ###   ########.fr       */
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

typedef struct player
{
	double	x;
	double	y;
	char	view;
}	t_player;

typedef struct map
{
	char	**map;
	int		max_x;
	int		max_y;
	int		*floor_color;
	int		*ceil_color;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_map;

typedef struct game
{
	t_map		*map;
	t_player	*player;
}	t_game;

//parse.c
t_game	*parse(char *argv);

//utils.c
void    free_all(t_game *game);

#endif