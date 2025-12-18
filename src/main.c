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
			//execution
			setup_run_game(game, game->map);
			// parsing free's:
			free_chart(game->map->chart, game->map->max_y);
			free_all(game);
		}
	}
	else
		printf("Invalid number of arguments: needs map file\n");
	return (0);
}
