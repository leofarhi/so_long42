/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:00:42 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 20:00:42 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static t_bool	init_map(t_game *game)
{
	game->map.cam.x = 0;
	game->map.cam.y = 0;
	game->map.entities = NULL;
	game->map.collectible_countdown = 0;
	game->map.grid = malloc(sizeof(t_tile *) * game->map.height);
	if (!game->map.grid)
		return (set_error(game, "Failed to malloc map"));
	return (SUCCESS);
}

static t_bool	set_tile_grid(t_game *game, char **grid, t_vector2 pos)
{
	if (grid[pos.y][pos.x] >= '0' && grid[pos.y][pos.x] <= '1')
		game->map.grid[pos.y][pos.x].tileset = (char)(grid[pos.y][pos.x] - '0');
	else
	{
		game->map.grid[pos.y][pos.x].tileset = 0;
		if (!spawn_entity(game, grid[pos.y][pos.x], pos.x, pos.y))
		{
			game->map.height = pos.y;
			return (set_error(game, "Failed to spawn entity"));
		}
	}
	return (SUCCESS);
}

static t_bool	load_loop_map(t_game *game, char **grid)
{
	t_vector2	pos;

	pos.y = 0;
	while (pos.y < (int)game->map.height)
	{
		game->map.grid[pos.y] = malloc(sizeof(t_tile) * game->map.width);
		if (!game->map.grid[pos.y])
			return (set_error(game, "Failed to malloc map"));
		pos.x = 0;
		while (pos.x < (int)game->map.width)
		{
			if (!set_tile_grid(game, grid, pos))
				return (FAILURE);
			pos.x++;
		}
		pos.y++;
	}
	return (SUCCESS);
}

t_bool	load_map(t_game *game, char **grid)
{
	if (!init_map(game))
		return (FAILURE);
	if (!load_loop_map(game, grid))
		return (FAILURE);
	update_tiles(game);
	return (SUCCESS);
}

void	free_map(t_game *game)
{
	size_t	i;

	i = 0;
	if (!game->map.grid)
		return ;
	while (i < game->map.height && game->map.grid[i])
		free(game->map.grid[i++]);
	free(game->map.grid);
}
