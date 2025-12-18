#include "cub3d.h"

static bool	store_textures(char **p, char *line, int i)
{
	int	len;

	if (*p)
	{
		printf("redefinition of a texture\n");
		return (false);
	}
	while (line[i] && line[i] == ' ')
		i++;
	len = ft_strlen(line) - 1;
	while (len > i && line[len] == ' ')
		len--;
	*p = ft_substr(line, i, len - i + 1);
	if (!*p)
	{
		printf("texture allocation failed\n");
		return (false);
	}
	if (!valid_file(*p, ".png", 5) || !access_texture(*p))
	{
		printf("invalid texture file\n");
		return (false);
	}
	return (true);
}

static bool	check_textures(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	line += i;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (store_textures(&map->north, line, 3));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (store_textures(&map->south, line, 3));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (store_textures(&map->west, line, 3));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (store_textures(&map->east, line, 3));
	else
		return (store_color(map, line));
}

static bool	texture_loop(t_game *game, t_map *map, char *line)
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
				printf("invalid map\n");
				return (false);
			}
			map->start_line++;
		}
		else
			map->max_y++;
		return (true);
	}
}

static bool	parse_textures(t_game *game, t_map *map, int fd)
{
	char	*line;
	int		len;

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

bool	open_textures(t_game *game, t_map *map, char *argv)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free_all(game);
		printf(".cub open failed\n");
		return (false);
	}
	return (parse_textures(game, map, fd));
}
