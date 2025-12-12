#include "cub3d.h"

void	free_chart(t_map *map, int y)
{
	int i = 0;
	while (i < y)
	{
		free(map->chart[i]);
		i++;
	}
	free(map->chart);
}

void    free_all(t_game *game)
{
	free(game->map->north);
	free(game->map->south);
	free(game->map->west);
	free(game->map->east);
	free (game->player);
	free (game->map);
	free (game);
}

bool    valid_file(char *argv, char *file, int len)
{
	int i;
	
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
			return(false);
		i++;
	}
	return (true);
}
int	check_state(t_map *map)
{
	if (map->floor_color && map->ceil_color && map->north && map->south && map->west && map->east)
		return (1);
	else
		return (0);
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