#include "cub3d.h"

static char	**copy_map(t_map *map, int *i)
{
	char	**copy;

	copy = malloc(sizeof(char *) * (map->max_y + 1));
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

static bool	closed_map(t_map *map, t_player *player)
{
	char	**copy;
	int		i;

	i = 0;
	copy = copy_map(map, &i);
	if (!copy)
	{
		printf("map copy failed\n");
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
		printf("unclosed map\n");
		free_chart(copy, i);
		return (false);
	}
}

static bool	valid_char(t_game *game, char c, int y, int x)
{
	int	len;

	len = ft_strlen(game->map->chart[y]) - 1;
	if (y == 0 || y == game->map->max_y || x == 0 || x == len)
	{
		if (c == '1')
			return (true);
		else if (c == ' ')
			return (valid_space(game->map, game->map->chart, y, x));
	}
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (valid_player(game, x, y, c));
	else if (c == ' ')
		return (valid_space(game->map, game->map->chart, y, x));
	else if (c == '0' || c == '1')
		return (true);
	printf("invalid map content\n");
	return (false);
}

bool	valid_content(t_game *game, t_map *map, char **chart)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < map->max_y)
	{
		j = 0;
		len = ft_strlen(chart[i]);
		while (chart[i][j])
		{
			if (!valid_char(game, chart[i][j], i, j))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_map(t_game *game, t_map *map, char **chart)
{
	if (map->max_y == 0)
	{
		printf("no map\n");
		return (false);
	}
	if (!valid_content(game, map, chart))
		return (false);
	if (!game->player->view)
	{
		printf("no player\n");
		return (false);
	}
	else
		return (closed_map(map, game->player));
}
