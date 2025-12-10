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
-------------------------------------

*/

/*
int	flood_fill(char **chart, int x, int y, int max_y)
{
	flood_fill(chart, x + 1, y, max_y);
	flood_fill(chart, x - 1, y, max_y);
	flood_fill(chart, x, y + 1, max_y);
	flood_fill(chart, x, y - 1, max_y);

}
*/

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
			{
				return (false);
			}
			j++;
		}
		i++;
	}
	print_player(game->player);
	if (!game->player)
		return (false);
	else
	{ //make a chart copy for flood_fill
		//if(!flood_fill(chart, j, i, map->max_y))
			//return (false);
		return (true);
	}
}

bool	parse_map(t_game *game, t_map *map, char *argv)
{
	char	*line;
	int 	len;
	int 	fd;
	int		i;

	i = 0;
	len = 0;
	map->chart = malloc(sizeof(char *)* (map->max_y + 1));
	if (!map->chart)
	{
		//free things
		return (false);
	}
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free_all(game);
		perror(".cub open failed");
		return (false);
	}
	while (i < map->max_y)
	{
		line = get_next_line(fd);
		if (!line)
			break; //free stuffff
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len-1] = '\0';
		len = ft_strlen(line);
		if (len > map->max_x)
			map->max_x = len;
		map->chart[i] = ft_strdup(line);
		if (!map->chart[i])
		{
			//freeeeeee
			return (false);
		}
		i++;
		free(line);
	}
	map->chart[i] = NULL;
	close (fd);
	validate_map(game, map, map->chart);
	return (true);

}
int	check_state(t_map *map)
{
	if (map->floor_color && map->ceil_color && map->north && map->south && map->west && map->east)
		return (1);
	else
		return (0);
}
bool	parse_textures(t_game *game, char *argv)
{
	char	*line;
	int		map_state;
	int 	len;
	//int		map_start = 0;
	int 	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free_all(game);
		perror(".cub open failed");
		return (false);
	}
	map_state = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len-1] = '\0';
		/*if (!map_state)
		{
			if (empty_lines(line));
				continue;
			if(!check_textures(game, game->map, line))
				return (false);
			map_state = check_state(game->map);

		}
		else
		{
			if (!empty_lines(line))*/
		game->map->max_y++;
		//}
		free(line);
	}
	close (fd);
	return (true);
}
