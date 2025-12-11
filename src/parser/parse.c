/*
open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday
*/ 

#include "cub3d.h"


t_game	*init_game()
{
	t_game *game;

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
	t_game *game;

	if (!valid_file(argv, ".cub", 5))
	{
		perror("invalid filename");
		return (NULL);
	}
	game = init_game();
	if (!game)
	{
		perror("memory allocation failed");
		return(NULL);
	}
	if (!parse_textures(game, argv))
	{
		return (NULL);
	}
	if (!parse_map(game, game->map, argv))
		return (NULL);
	return (game);
}
