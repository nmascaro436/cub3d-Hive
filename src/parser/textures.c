#include "cub3d.h"

int	get_color(char	*line)
{
    char    **temp
    int red;
    int green;
    int blue;
  
    line +=2;
/*
    red = ft_atoi(temp[0]);
    green = ft_atoi(temp[1]);
    blue = ft_atoi(temp[2]);
    */
}

bool	*store_textures(char **p, char *line)
{
	//more valid checks????
	int len;

	len = strlen(line) - 3;
	*p = ft_substr(line, 3 , len);
	if (!p)
		return(NULL)
	if (!valid_file(*p, ".xpm", 5))
	{
		free(*p);
		free_all(game);
		return(false);
	}
	return (true);
}


bool	check_textures(t_game game, t_map *map, char *line)
{
	if (!map->north && ft_strncmp(line, "NO ", 3) == 0)
		return (store_textures(&map->north, line));
	if (!map->south && ft_strncmp(line, "SO ", 3) == 0)
		return (store_textures(&map->south, line));
	if (!map->west && ft_strncmp(line, "WE ", 3) == 0)
		return (store_textures(&map->west, line));
	if (!map->east && ft_strncmp(line, "EA ", 3) == 0)
		return (store_textures(&map->east, line));
	if ((!map->floor_color && ft_strncmp(line, "F ", 2) == 0))
	{
		map->floor_color = get_color(line);
		if (map->floor_color < 0)
			return(false);
		else
			return(true);
	}
	if ((!map->ceil_color && ft_strncmp(line, "C ", 2) == 0))
	{
		map->ceil_color = get_color(line);
		if (map->ceil_color < 0)
			return(false);
		else
			return(true);
	}
	return (false);
}