#include "cub3d.h"

bool	access_texture(char	*p)
{
	int fd;

	fd = open(p, O_RDONLY);
	if (fd < 0)
		return(false);
	close (fd);
	return (true);

}

bool	valid_file(char *argv, char *file, int len)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	while (i > 0)
	{
		if (argv[i] == '.')
		{
			if (ft_strncmp(&argv[i], file, len) == 0)
				return (true);
			else
				return (false);
		}
		i--;
	}
	return (false);
}

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (true);
	while (line[i])
	{
		if (line[i] != ' ' || line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	map_state(t_map *map)
{
	if (map->floor_color && map->ceil_color
		&& map->north && map->south && map->west && map->east)
		return (1);
	else
		return (0);
}
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

void	print_map(t_map *map)
{
	int i = 0;
	while(map->chart[i])
	{
		printf("%s\n", map->chart[i]);
		i++;
	}
	printf("mapX = %d\n", map->max_x);
	printf("mapY = %d\n", map->max_y);
	printf("\n");
}
void	print_player(t_player *player)
{
	printf("player_x = %f\n", player->x);
	printf("player_y = %f\n", player->y);
	printf("player_view = %c\n", player->view);
	printf("\n");
}
void	print_textures(t_map *map)
{
	printf("north = %s\n", map->north);
	printf("south = %s\n", map->south);
	printf("west = %s\n", map->west);
	printf("east = %s\n", map->east);
	printf("floor color = %u\n", map->floor_color);
	printf("ceil color = %u\n", map->ceil_color);
	printf("\n");
}