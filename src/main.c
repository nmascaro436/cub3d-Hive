#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 2)
	{
		game = parse(argv[1]);
		if (game)
		{
			//test printing:
			print_map(game->map);
			print_player(game->player);
			print_textures(game->map);
			// parsing free's:
			free_chart(game->map, game->map->max_y);
			free_all(game);
		}
	}
	return (0);
}
