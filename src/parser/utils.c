#include "cub3d.h"

void    free_all(t_game *game)
{
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
			if (ft_strncmp(&argv[i], "file", len) == 0)
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}