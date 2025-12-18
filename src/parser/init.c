#include "cub3d.h"

static t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		free(game);
		return (NULL);
	}
	ft_memset(game->map, 0, sizeof(t_map));
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		free(game->map);
		free(game);
		return (NULL);
	}
	ft_memset(game->player, 0, sizeof(t_player));
	return (game);
}

t_game	*parse(char *argv)
{
	t_game	*game;

	if (!valid_file(argv, ".cub", 5))
	{
		printf("invalid filename\n");
		return (NULL);
	}
	game = init_game();
	if (!game)
	{
		printf("memory allocation failed\n");
		return (NULL);
	}
	if (!open_textures(game, game->map, argv))
		return (NULL);
	if (!parse_map(game, game->map, argv))
		return (NULL);
	if (!validate_map(game, game->map, game->map->chart))
	{
		free_chart(game->map->chart, game->map->max_y);
		free_all(game);
		return (NULL);
	}
	return (game);
}
