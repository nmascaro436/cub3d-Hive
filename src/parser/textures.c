#include "cub3d.h"

uint32_t	get_color(char	*line)
{
	int	color[3];
	int	i;
	int	j;

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	i = 2;
	j = 0;
	while (line[i] && j < 3)
	{
		while (line[i] == ' ')
			i++;
		while (line[i] && ft_isdigit(line[i]))
		{
			color[j] = color[j] * 10 + line[i] - '0';
			i++;
		}
		j++;
		if (!line[i])
			break ;
		if (line[i] != ',')
			return (-2);
		i++;
	}
	if (j != 3)
		return (-1);
	while (j > 0)
	{
		j--;
		if (color[j] > 255 || color[j] < 0)
			return (-1);
	}
	return ((color[0] << 24) | (color[1] << 16) | (color[2] << 8) | 0xFF);
}

bool	store_color(t_map *map, char *line)
{
	if ((!map->floor_color && ft_strncmp(line, "F ", 2) == 0))
	{
		map->floor_color = get_color(line);
		if (map->floor_color < 0)
		{
			perror("invalid floor color");
			return (false);
		}
		else
			return (true);
	}
	else if ((!map->ceil_color && ft_strncmp(line, "C ", 2) == 0))
	{
		map->ceil_color = get_color(line);
		if (map->ceil_color < 0)
		{
			perror("invalid ceiling color");
			return (false);
		}
		else
			return (true);
	}
	return (false);
}

bool	store_textures(char **p, char *line)
{
	int	len;
	int	i;

	i = 3;
	if (*p)
	{
		perror("redefinition of a texture");
		return (false);
	}
	while (line[i] == ' ')
		i++;
	len = ft_strlen(line) - i;
	*p = ft_substr(line, i, len);
	if (!*p)
	{
		perror("texture allocation failed");
		return (false);
	}
	if (!valid_file(*p, ".png", 5))
	{
		perror("invalid texture file");
		return (false);
	}
	return (true);
}

bool	check_textures(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (store_textures(&map->north, line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (store_textures(&map->south, line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (store_textures(&map->west, line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (store_textures(&map->east, line));
	else
		return (store_color(map, line));
}
