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

static char set_id(char side[3], char idx[5])
{
	int id;

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
	tile->ids[0] = set_id((char[3]){local[0][0],local[0][1],local[1][0]}, (char[5]){8, 13, 2, 12, 9});
	tile->ids[1] = set_id((char[3]){local[0][2],local[0][1],local[1][2]}, (char[5]){11, 14, 3, 15, 10});
	tile->ids[2] = set_id((char[3]){local[2][0],local[2][1],local[1][0]}, (char[5]){20, 17, 6, 16, 21});
	tile->ids[3]  = set_id((char[3]){local[2][2],local[2][1],local[1][2]}, (char[5]){23, 18, 7, 19, 22, });
}

/*local[y][x]*/
static void	set_tile(t_game *game, size_t x, size_t y)
{
	char	local[3][3];
	char	obj;
	t_tile	**grid;

	grid = game->map.grid;
	obj = grid[y][x].tileset;
	local[0][0] = (y == 0 || x == 0) ? 0 : grid[y-1][x-1].tileset == obj;
	local[0][1] = (y == 0) ? 0 : grid[y-1][x].tileset == obj;
	local[0][2] = (y == 0 || x == game->map.width - 1) ? 0 : grid[y-1][x+1].tileset == obj;
	local[1][0] = (x == 0) ? 0 : grid[y][x-1].tileset == obj;
	local[1][1] = grid[y][x].tileset == obj;
	local[1][2] = (x == game->map.width - 1) ? 0 : grid[y][x+1].tileset == obj;
	local[2][0] = (y == game->map.height - 1 || x == 0) ? 0 : grid[y+1][x-1].tileset == obj;
	local[2][1] = (y == game->map.height - 1) ? 0 : grid[y+1][x].tileset == obj;
	local[2][2] = (y == game->map.height - 1 || x == game->map.width - 1) ? 0 : grid[y+1][x+1].tileset == obj;
	set_tile_local(local, &game->map.grid[y][x]);
}

static void update_tiles(t_game *game)
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

t_bool	load_map(t_game *game, char **grid)
{
	size_t	x;
	size_t	y;

	y = 0;
	game->map.grid = malloc(sizeof(t_tile *) * game->map.height);//TODO: Protect malloc
	if (!game->map.grid)
		return (print_error("Failed to malloc map"));//TODO check if we need to free data
	while (y < game->map.height)
	{
		game->map.grid[y] = malloc(sizeof(t_tile) * game->map.width);//TODO: Protect malloc
		if (!game->map.grid[y])
			return (print_error("Failed to malloc map"));//TODO clear map
		x = 0;
		while (x < game->map.width)
		{
			if (grid[y][x] >= '0' && grid[y][x] <= '1')
				game->map.grid[y][x].tileset = (char)(grid[y][x] - '0');
			else
			{
				game->map.grid[y][x].tileset = 0;
				//if (!spawn_entity(game, grid[y][x], x, y))
				//	return (print_error("Failed to spawn entity"));//TODO clear map
			}
			x++;
		}
		y++;
	}
	update_tiles(game);
	return (SUCCESS);
}

void	free_map(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map.height)
		free(game->map.grid[i++]);
	free(game->map.grid);
}