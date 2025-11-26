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

t_game	*parse(char *argv)
{
	if (!valid_args(argv))
		return (NULL);
	return (NULL);
}
