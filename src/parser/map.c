#include "cub3d.h"

static bool	fill_map(t_game *game, t_map *map, char *line, int j)
{
	int	len;

	len = 0;
	if (j < map->max_y)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		len = ft_strlen(line);
		if (len > map->max_x)
			map->max_x = len;
		map->chart[j] = ft_strdup(line);
		if (!map->chart[j])
		{
			free_chart(map->chart, j - 1);
			free_all(game);
			return (false);
		}
	}
	map->chart[j + 1] = NULL;
	return (true);
}

static bool	map_loop(t_game *game, t_map *map, int fd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (i >= map->start_line)
		{
			if (!fill_map(game, map, line, j))
			{
				free (line);
				return (false);
			}
			j++;
		}
		i++;
		free(line);
	}
	return (true);
}

bool	parse_map(t_game *game, t_map *map, char *argv)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free_all(game);
		perror(".cub open failed");
		return (false);
	}
	map->chart = malloc(sizeof(char *) * (map->max_y + 1));
	if (!map->chart)
	{
		free_all(game);
		close(fd);
		return (false);
	}
	if (!map_loop(game, map, fd))
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
