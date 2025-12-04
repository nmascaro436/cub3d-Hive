#include "cub3d.h"

/*NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

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
*/





bool	parse_map(t_game *game, int fd)
{
	char	*line;
	int		map_state;
	int 	len;

	map_state = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		len = ft_strlen(line);
		line[len-1] = '\0'
		if (!map_state)
		{
			if (empty_lines(line))
				continue;
			if(!check_textures(game, game->map, line))
				return (false);
		}
		else
			store_map(game);
		//textures
		//color
		//map
	}
	return (true)

}
