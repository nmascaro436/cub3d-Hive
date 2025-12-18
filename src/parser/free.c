#include "cub3d.h"

void	free_chart(char **chart, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		free(chart[i]);
		i++;
	}
	free(chart);
}

void	free_all(t_game *game)
{
	free(game->map->north);
	free(game->map->south);
	free(game->map->west);
	free(game->map->east);
	free(game->player);
	free(game->map);
	free(game);
}
