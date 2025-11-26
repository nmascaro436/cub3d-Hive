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

/*open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday
*/


#include "cub3d.h"

t_game	*parse(char **argv)
{
    
    return(NULL);

}