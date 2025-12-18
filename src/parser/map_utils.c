/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:32:40 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/18 14:32:41 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	valid_space_y(t_map *map, char **chart, int y, int x)
{
	if (y < (map->max_y - 1))
	{
		if (x > 0 && x < (int)(ft_strlen(chart[y + 1]) - 1))
		{
			if (chart[y + 1][x] != '1' && chart[y + 1][x] != ' ' )
			{
				printf("unclosed space\n");
				return (false);
			}
		}
	}
	if (y > 0)
	{
		if (x > 0 && x < (int)(ft_strlen(chart[y - 1]) - 1))
		{
			if (chart[y - 1][x] != '1' && chart[y - 1][x] != ' ' )
			{
				printf("unclosed space\n");
				return (false);
			}
		}
	}
	return (true);
}

bool	valid_space(t_map *map, char **chart, int y, int x)
{
	if (x < (int)(ft_strlen(map->chart[y]) - 1))
	{
		if (chart[y][x + 1] != '1' && chart[y][x + 1] != ' ' )
		{
			printf("unclosed space\n");
			return (false);
		}
	}
	if (x > 0)
	{
		if (chart[y][x - 1] != '1' && chart[y][x - 1] != ' ' )
		{
			printf("unclosed space\n");
			return (false);
		}
	}
	return (valid_space_y(map, chart, y, x));
}

bool	valid_player(t_game *game, int x, int y, char c)
{
	if (game->player->view)
	{
		printf("too many players\n");
		return (false);
	}
	else
	{
		game->map->player = game->player;
		game->player->x = (double)x;
		game->player->y = (double)y;
		game->player->view = c;
		return (true);
	}
}

int	flood_fill(char **copy, int x, int y, int max_y)
{
	int	max_x;

	if (y < 0 || y >= max_y)
		return (0);
	max_x = ft_strlen(copy[y]);
	if (x < 0 || x >= max_x)
		return (0);
	if (copy[y][x] == ' ')
		return (0);
	if (copy[y][x] == 'T' || copy[y][x] == '1')
		return (1);
	else
		copy[y][x] = 'T';
	if (!flood_fill(copy, x + 1, y, max_y))
		return (0);
	if (!flood_fill(copy, x - 1, y, max_y))
		return (0);
	if (!flood_fill(copy, x, y + 1, max_y))
		return (0);
	if (!flood_fill(copy, x, y - 1, max_y))
		return (0);
	return (1);
}
