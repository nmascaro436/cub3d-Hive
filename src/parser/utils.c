#include "cub3d.h"

void	free_chart(t_map *map)
{
	int i = 0;
	while (i < map->max_y)
	{
		free(map->chart[i]);
		i++;
	}
	free (map->chart);

}

void    free_all(t_game *game)
{
	if (game->map->chart)
		free_chart(game->map);
	free (game->player);
	free (game->map);
	free (game);   
}

bool    valid_file(char *argv, char *file, int len)
{
	int i;
	
	i = 0;
	while (argv[i])
	{
		if (argv[i] == '.')
		{
			if (ft_strncmp(&argv[i], file, len) == 0)
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
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
}
void	print_player(t_player *player)
{
	printf("player_x = %f\n", player->x);
	printf("player_y = %f\n", player->y);
	printf("player_view = %c\n", player->view);
}