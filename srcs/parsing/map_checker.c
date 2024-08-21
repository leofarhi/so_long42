/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:32:21 by lfarhi            #+#    #+#             */
/*   Updated: 2024/07/08 15:13:19 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static t_bool	check_border(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map.width)
	{
		if (game->map.grid[i][0].tileset != 1
			|| game->map.grid[i][game->map.height - 1].tileset != 1)
			return (set_error(game, "Map is not surrounded by walls"));
		i++;
	}
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[0][i].tileset != 1
			|| game->map.grid[game->map.width - 1][i].tileset != 1)
			return (set_error(game, "Map is not surrounded by walls"));
		i++;
	}
	return (SUCCESS);
}

static t_bool	check_entities(t_game *game)
{
	if (!game->exit)
		return (set_error(game, "Map has no exit"));
	if (!game->player)
		return (set_error(game, "Map has no player"));
	if (!game->map.collectible_countdown)
		return (set_error(game, "Map has no collectibles"));
	return (SUCCESS);
}

static	t_bool	check_collectible(t_game *game)
{
	t_list		*curr;
	t_entity	*entity;
	t_bool		e_path;

	e_path = TRUE;
	curr = game->map.entities;
	while (curr)
	{
		entity = (t_entity *)curr->content;
		if (entity->id == 'C')
		{
			e_path &= exists_path(game,
					(t_vector2){entity->pos.x / TILE_SIZE,
					entity->pos.y / TILE_SIZE},
					(t_vector2){game->player->pos.x / TILE_SIZE,
					game->player->pos.y / TILE_SIZE});
		}
		curr = curr->next;
	}
	if (!e_path)
		return (set_error(game, "Collectible is not reachable"));
	return (SUCCESS);
}

static t_bool	check_end(t_game *game)
{
	t_bool	e_path;

	e_path = exists_path(game,
			(t_vector2){game->exit->pos.x / TILE_SIZE,
			game->exit->pos.y / TILE_SIZE},
			(t_vector2){game->player->pos.x / TILE_SIZE,
			game->player->pos.y / TILE_SIZE});
	if (!e_path)
		return (set_error(game, "Exit is not reachable"));
	return (SUCCESS);
}

t_bool	map_checker(t_game *game)
{
	return (check_border(game)
		&& check_entities(game)
		&& check_collectible(game)
		&& check_end(game));
}
