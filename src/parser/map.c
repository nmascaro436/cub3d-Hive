#include "cub3d.h"

/*NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

# Textures
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

# Colors (RGB)
F 220,100,0       # Floor
C 225,30,0        # Ceiling

# Map layout
1111111111
1000000001
1000N00001
1000000001
1111111111

validate closed walls, 1 player
store player pos. 
allow spaces
-------------------------------------

*/


int	flood_fill(char **copy, int x, int y, int max_y)
{
	int max_x;

	if (y < 0 || y > max_y)
		return (0);
	max_x = ft_strlen(copy[y]);
	if (x < 0 || x > max_x)
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

bool	closed_map(t_map *map, char	**chart, t_player *player)
{
	char **copy;
	int	i = 0;

	copy = malloc(sizeof(char *)*(map->max_y + 1));
	if (!copy)
	{
		//freeeeeeee
		return(false);
	}
	while (i < map->max_y)
	{
		copy[i] = ft_strdup(chart[i]);
		i++;
	}
	copy[i] = NULL;
	if (flood_fill(copy, (int)player->x, (int)player->y, map->max_y))
	{
		//free copy??
		return(true);
	}
	else
	{
		//free??
		return(false);
	}
}

bool	valid_char(t_game *game, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (game->player->view) // needs
		{
			return (false); //more than 1 player, clean uppppppppppp
		}
		else
		{
			game->map->player = game->player; // added this
			game->player->x = (double)x;
			game->player->y = (double)y;
			game->player->view = c;
			return (true);
		}
	}
	else if (c == '0' || c == '1' || c == ' ')
		return (true);
	return (false);
}

bool	validate_map(t_game *game, t_map *map, char **chart)
{
	int i;
	int j;

	i = 0;
	while (i < map->max_y)
	{
		j = 0;
		while (chart[i][j])
		{
			if (!valid_char(game, chart[i][j], i, j))
				return (false);
			j++;
		}
		i++;
	}
	if (!game->player)
		return (false);
	else
	{
		if (!closed_map(map, chart, game->player))
			return (false);
		game->player->x += 0.5;
		game->player->y += 0.5;
		return (true);
	}
}
