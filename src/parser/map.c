#include "cub3d.h"

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

char	**copy_map(t_map *map, int *i)
{
	char	**copy;

	copy = malloc(sizeof(char *)*(map->max_y + 1));
	if (!copy)
		return (NULL);
	while (*i < map->max_y)
	{
		copy[*i] = ft_strdup(map->chart[*i]);
		if (!copy[*i])
		{
			free_chart(copy, *i);
			return (NULL);
		}
		(*i)++;
	}
	copy[*i] = NULL;
	return (copy);
}

bool	closed_map(t_map *map, t_player *player)
{
	char	**copy;
	int		i;

	i = 0;
	copy = copy_map(map, &i);
	if (!copy)
	{
		perror ("map copy failed");
		return (false);
	}
	if (flood_fill(copy, (int)player->x, (int)player->y, map->max_y))
	{
		player->x += 0.5;
		player->y += 0.5;
		free_chart(copy, i);
		return (true);
	}
	else
	{
		perror("unclosed map");
		free_chart(copy, i);
		return (false);
	}
}

bool	valid_char(t_game *game, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (game->player->view)
		{
			perror("too many players");
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
	else if (c == '0' || c == '1' || c == ' ')
		return (true);
	perror ("invalid map content");
	return (false);
}

bool	validate_map(t_game *game, t_map *map, char **chart)
{
	int	i;
	int	j;

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
	if (!game->player->view)
	{
		perror("no player");
		return (false);
	}
	else
		return (closed_map(map, game->player));
}
