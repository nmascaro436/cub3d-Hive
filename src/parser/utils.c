/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:32:55 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/18 14:32:56 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	access_texture(char	*p)
{
	int	fd;

	fd = open(p, O_RDONLY);
	if (fd < 0)
		return (false);
	close (fd);
	return (true);
}

bool	valid_file(char *argv, char *file, int len)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	while (i > 0)
	{
		if (argv[i] == '.')
		{
			if (ft_strncmp(&argv[i], file, len) == 0)
				return (true);
			else
				return (false);
		}
		i--;
	}
	return (false);
}

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (true);
	while (line[i])
	{
		if (line[i] != ' ' || line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

int	map_state(t_map *map)
{
	if (map->floor_color && map->ceil_color
		&& map->north && map->south && map->west && map->east)
		return (1);
	else
		return (0);
}
