#include "cub3d.h"

static bool	build_color(uint32_t *col, int color[3], int j)
{
	if (j != 3)
		return (false);
	while (j > 0)
	{
		j--;
		if (color[j] > 255 || color[j] < 0)
			return (false);
	}
	*col = ((color[0] << 24) | (color[1] << 16) | (color[2] << 8) | 0xFF);
	return (true);
}

static int	build_rgb(int color[3], char *line, int i, int j)
{
	while (line[i] && ft_isdigit(line[i]))
	{
		color[j] = color[j] * 10 + line[i] - '0';
		i++;
	}
	return (i);
}

static bool	get_color(uint32_t *col, char *line, int i, int j)
{
	int	color[3];

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	while (line[i] && j < 3)
	{
		while (line[i] == ' ')
			i++;
		if (!ft_isdigit(line[i]))
			return (false);
		i = build_rgb(color, line, i, j);
		j++;
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (j == 3 && line[i])
			return (false);
		if (line[i] == ',' && j < 3)
			i++;
		else
			return (false);
	}
	return (build_color(col, color, j));
}

bool	store_color(t_map *map, char *line)
{
	if ((!map->floor_color && ft_strncmp(line, "F ", 2) == 0))
	{
		if (!get_color(&map->floor_color, line, 2, 0))
		{
			printf("invalid floor color\n");
			return (false);
		}
		else
			return (true);
	}
	else if ((!map->ceil_color && ft_strncmp(line, "C ", 2) == 0))
	{
		if (!get_color(&map->ceil_color, line, 2, 0))
		{
			printf("invalid ceiling color\n");
			return (false);
		}
		else
			return (true);
	}
	else
		printf("invalid/missing textures\n");
	return (false);
}
