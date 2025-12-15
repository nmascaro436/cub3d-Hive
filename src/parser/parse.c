#include "cub3d.h"

bool	fill_map(t_game *game, t_map *map, char *line, int j)
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
	else if (j == map->max_y)
		map->chart[j] = NULL;
	return (true);
}

bool	parse_map(t_game *game, t_map *map, char *argv)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	i = 0;
	j = 0;
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
				close (fd);
				return (false);
			}
			j++;
		}
		i++;
		free(line);
	}
	close(fd);
	return (true);
}

bool	texture_loop(t_game *game, t_map *map, char *line)
{
	if (!map_state(map))
	{
		game->map->start_line++;
		if (empty_line(line))
			return (true);
		else
			return (check_textures(map, line));
	}
	else
	{
		if (empty_line(line))
		{
			if (map->max_y > 0)
			{
				perror ("invalid map");
				return (false);
			}
			map->start_line++;
		}
		else
			map->max_y++;
		return(true);
	}
}

bool	parse_textures(t_game *game, t_map *map, char *argv)
{
	char	*line;
	int		len;
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free_all(game);
		perror(".cub open failed");
		return (false);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!texture_loop(game, map, line))
		{
			free(line);
			free_all(game);
			close(fd);
			return (false);
		}
		free(line);
	}
	close (fd);
	return (true);
}
