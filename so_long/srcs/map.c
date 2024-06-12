/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:44:38 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 15:43:15 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int set_id(char side[3], char idx[5])
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


static void	set_tile_local(char local[3][3], t_tile *tile, t_type *type)
{
	int index;

	index = set_id((char[3]){local[0][0],local[0][1],local[1][0]}, (char[5]){4, 9, 0, 8, 5});
	tile->textures[0] = type->textures[index];
	index = set_id((char[3]){local[0][2],local[0][1],local[1][2]}, (char[5]){7, 10, 1, 11, 6});
	tile->textures[1] = type->textures[index];
	index = set_id((char[3]){local[2][0],local[2][1],local[1][0]}, (char[5]){16, 13, 2, 12, 17});
	tile->textures[2] = type->textures[index];
	index = set_id((char[3]){local[2][2],local[2][1],local[1][2]}, (char[5]){19, 14, 3, 15, 18});
	tile->textures[3] = type->textures[index];
}

/*local[y][x]*/
static void	set_tile(t_window *window, char **grid, size_t x, size_t y)
{
	char	local[3][3];
	char	obj;
	t_type	type;

	obj = grid[y][x];
	type = window->assets.types[(int)obj - '0'];
	local[0][0] = (y == 0 || x == 0) ? 0 : grid[y-1][x-1] == obj;
	local[0][1] = (y == 0) ? 0 : grid[y-1][x] == obj;
	local[0][2] = (y == 0 || x == window->map.width - 1) ? 0 : grid[y-1][x+1] == obj;
	local[1][0] = (x == 0) ? 0 : grid[y][x-1] == obj;
	local[1][1] = grid[y][x] == obj;
	local[1][2] = (x == window->map.width - 1) ? 0 : grid[y][x+1] == obj;
	local[2][0] = (y == window->map.height - 1 || x == 0) ? 0 : grid[y+1][x-1] == obj;
	local[2][1] = (y == window->map.height - 1) ? 0 : grid[y+1][x] == obj;
	local[2][2] = (y == window->map.height - 1 || x == window->map.width - 1) ? 0 : grid[y+1][x+1] == obj;
	set_tile_local(local, &window->map.grid[y][x], &type);
}

int	load_map(t_window *window, char **grid)
{
	size_t	x;
	size_t	y;

	y = 0;
	window->map.grid = malloc(sizeof(t_tile *) * window->map.height);//TODO: Protect malloc
	if (!window->map.grid)
		return (print_error("Failed to malloc map"));
	while (y < window->map.height)
	{
		window->map.grid[y] = malloc(sizeof(t_tile) * window->map.width);//TODO: Protect malloc
		if (!window->map.grid[y])
			return (print_error("Failed to malloc map"));
		x = 0;
		while (x < window->map.width)
		{
			window->map.grid[y][x].type = grid[y][x];
			if (!(grid[y][x] >= '0' && grid[y][x] <= '1'))
			{
				spawn_entity(window, grid[y][x], x, y);
				grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	y = 0;
	while (y < window->map.height)
	{
		x = 0;
		while (x < window->map.width)
		{
			set_tile(window, grid, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

void	draw_map(t_window *window)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < window->map.height)
	{
		x = 0;
		while (x < window->map.width)
		{
			tile_draw(window, &window->map.grid[y][x],
				(x * TILE_SIZE) + window->map.cam[0],
				(y * TILE_SIZE) + window->map.cam[1]);
			x++;
		}
		y++;
	}
}