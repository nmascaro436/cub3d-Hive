/*Open .cub file → read line by line.
Identify and validate textures.
Identify and validate floor/ceiling colors.
Identify map lines → build 2D map structure.
Validate map integrity (walls, single player, valid characters).

# Textures
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

# Colors (RGB)
F 220,100,0       # Floor
C 225,30,0        # Ceiling

# Map layout
1111111111
1000000001
1000N00001
1000000001
1111111111

open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday
*/ 

#include "cub3d.h"

bool    valid_args(char *argv)
{
	int i;
	
	i = 0;
	while (argv[i])
	{
		if (argv[i] == '.')
		{
			if (ft_strncmp(&argv[i], ".cub", 5) == 0)
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}
t_game	*init_game()
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	//ft_memset(game, 0, sizeof(t_game));
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
	int	fd;

	if (!valid_args(argv))
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
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free_all(game);
		perror(".cub open failed");
		return (NULL);
	}
	if (!parse_map(game->map, fd))
		return (NULL);
	return (game);
}
