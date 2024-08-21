/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:29:20 by lfarhi            #+#    #+#             */
/*   Updated: 2024/07/08 15:56:11 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static char	set_id(char side[3], char idx[5])
{
	int	id;

	id = 0;
	if (side[1])
	{
		if (side[2])
		{
			if (side[0])
				id = 1;
			else
				id = 2;
		}
		else
			id = 3;
	}
	else if (side[2])
		id = 4;
	return (idx[id]);
}

static void	set_tile_local(char local[3][3], t_tile *tile)
{
	tile->ids[0] = set_id((char [3]){local[0][0], local[0][1], local[1][0]},
			(char [5]){8, 13, 2, 12, 9});
	tile->ids[1] = set_id((char [3]){local[0][2], local[0][1], local[1][2]},
			(char [5]){11, 14, 3, 15, 10});
	tile->ids[2] = set_id((char [3]){local[2][0], local[2][1], local[1][0]},
			(char [5]){20, 17, 6, 16, 21});
	tile->ids[3] = set_id((char [3]){local[2][2], local[2][1], local[1][2]},
			(char [5]){23, 18, 7, 19, 22});
}

static char	check(t_game *game, int condition, t_vector2 pos, char obj)
{
	if (condition)
		return (game->map.grid[pos.y][pos.x].tileset == obj);
	return (0);
}

/*local[y][x]*/
static void	set_tile(t_game *game, size_t x, size_t y)
{
	char	local[3][3];
	char	obj;
	t_tile	**grid;

	grid = game->map.grid;
	obj = grid[y][x].tileset;
	local[0][0] = check(game, y != 0 && x != 0,
			(t_vector2){x - 1, y - 1}, obj);
	local[0][1] = check(game, y != 0, (t_vector2){x, y - 1}, obj);
	local[0][2] = check(game, y != 0 && x != game->map.width - 1,
			(t_vector2){x + 1, y - 1}, obj);
	local[1][0] = check(game, x != 0, (t_vector2){x - 1, y}, obj);
	local[1][1] = grid[y][x].tileset == obj;
	local[1][2] = check(game, x != game->map.width - 1,
			(t_vector2){x + 1, y}, obj);
	local[2][0] = check(game, y != game->map.height - 1 && x != 0,
			(t_vector2){x - 1, y + 1}, obj);
	local[2][1] = check(game, y != game->map.height - 1,
			(t_vector2){x, y + 1}, obj);
	local[2][2] = check(game, y != game->map.height - 1
			&& x != game->map.width - 1, (t_vector2){x + 1, y + 1}, obj);
	set_tile_local(local, &game->map.grid[y][x]);
}

void	update_tiles(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			set_tile(game, x, y);
			x++;
		}
		y++;
	}
}
