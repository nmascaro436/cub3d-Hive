#include "cub3d.h"

uint32_t	get_color(char	*line)
{
	int color[3] = {0, 0, 0};
	int	i;
	int	j;
  
	i = 2;
	j = 0;
	while(line[i] && j < 3)
	{
		while (ft_isdigit(line[i]))
		{
			color[j] = color[j] * 10 +line[i] - '0';
			i++;
		}
		if (line[i] != ',' && line[i] != '\0') //&& ft_isdigit(line[i+1]))
			return (-2);
		i++;
		j++;
		
	}
	if (j != 3)
		return(-1);
	while(j > 0)
	{
		j--;
		if (color[j] > 255 || color[j] < 0)
			return(-1);
		
	}
	uint32_t res = ((color[0] << 24) | (color[1] << 16) | (color[2] << 8) | 0xFF);
	return (res);
}

bool	store_color(t_map *map, char *line)
{
	if ((!map->floor_color && ft_strncmp(line, "F ", 2) == 0))
	{
		map->floor_color = get_color(line);
		if (map->floor_color < 0)
			return(false);//free stuff
		else
			return(true);
	}
	else if ((!map->ceil_color && ft_strncmp(line, "C ", 2) == 0))
	{
		map->ceil_color = get_color(line);
		if (map->ceil_color < 0)
			return(false); //free stuff
		else
			return(true);
	}
	return (false);
}

bool	store_textures(char **p, char *line)
{
	int len;

	len = ft_strlen(line) - 3;
	*p = ft_substr(line, 3 , len);
	if (!*p)
	{
		return(false);
	}
	if (!valid_file(*p, ".png", 5))
	{
	//	free(*p);
		return(false);
	}
	return (true);
}


bool	check_textures(t_map *map, char *line)
{
	
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		
		if (map->north)
			return (false);
		else
			return (store_textures(&map->north, line));
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map->south)
			return (false);
		else
			return (store_textures(&map->south, line));
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		
		if (map->west)
			return(false);
		else
			return (store_textures(&map->west, line));
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{	
		if (map->east)
			return (false);
		else
			return (store_textures(&map->east, line));
	}
	else
		return (store_color(map, line));//free stuff
}


