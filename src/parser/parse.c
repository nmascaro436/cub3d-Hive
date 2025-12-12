#include "cub3d.h"

bool	parse_map(t_game *game, t_map *map, char *argv)
{
	char	*line;
	int 	len;
	int 	fd;
	int		i;
	int j = 0;

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
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (i >= map->start_line)
		{
			if (j < map->max_y)
			{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len-1] = '\0';
			len = ft_strlen(line);
			if (len > map->max_x)
				map->max_x = len;
			map->chart[j] = ft_strdup(line);
			if (!map->chart[j])
			{
				free_chart(map, j-1);
				free_all(game);
				return (false);
			}
			j++;
			}
		}
		i++;
		free(line);
	}
	map->chart[j] = NULL;
	close (fd);
	return(true);
}


bool	parse_textures(t_game *game, t_map *map, char *argv)
{
	char	*line;
	int 	len;
	int		map_state = 0;
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
		if (!map_state)
		{
			game->map->start_line++;
			if (empty_line(line))
			{
				free (line);
				continue;
			}
			if(!check_textures(map, line))
			{
				free(line);
				free_all(game);
				close(fd);
				return(false);
			}
			map_state = check_state(map);
		}
		else
		{
			if (!map->max_y && empty_line(line))
			{
				map->start_line++;
				free (line);
				continue;
			}
			else
			{
				if (empty_line(line))
				{
					free(line);
					free_all(game);
					close(fd);
					perror ("invalid map");
					return(false);
				}
				map->max_y++;
			}
		}
		free(line);
	}
	close (fd);
	return (true);
}
