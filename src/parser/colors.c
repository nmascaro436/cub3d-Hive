#include "cub3d.h"

static uint32_t	build_color(int color[3], int j)
{
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

static uint32_t	get_color(char	*line, int i, int j)
{
	int	color[3];

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	while (line[i] && j < 3)
	{
		while (line[i] == ' ')
			i++;
		while (line[i] && ft_isdigit(line[i]))
		{
			color[j] = color[j] * 10 + line[i] - '0';
			i++;
		}
		while (line[i] && line[i] == ' ')
			i++;
		j++;
		if (!line[i])
			break ;
		if (line[i] != ',')
			return (-1);
		i++;
	}
	return (build_color(color, j));
}

bool	store_color(t_map *map, char *line)
{
	if ((!map->floor_color && ft_strncmp(line, "F ", 2) == 0))
	{
		map->floor_color = get_color(line, 2, 0);
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
		map->ceil_color = get_color(line, 2, 0);
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
