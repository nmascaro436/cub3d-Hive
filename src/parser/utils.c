#include "cub3d.h"

void    free_all(t_game *game)
{
	free (game->player);
	free (game->map);
	free (game);   
}