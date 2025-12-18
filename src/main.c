/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:32:58 by nmascaro          #+#    #+#             */
/*   Updated: 2025/12/18 14:33:00 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 2)
	{
		game = parse(argv[1]);
		if (game)
		{
			setup_run_game(game, game->map);
			free_chart(game->map->chart, game->map->max_y);
			free_all(game);
		}
	}
	else
		printf("Invalid number of arguments: needs map file\n");
	return (0);
}
