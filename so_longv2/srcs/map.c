/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:57:43 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 19:57:43 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	draw_tile(t_game *game, t_tile *tile, t_vector2 pos)
{
	int	size;

	size = TILE_SIZE / 2;
	mlxe_draw_subtexture(game->window,
		game->assets.tilesets[(int)tile->tileset],
		pos,
		(t_rect){(tile->ids[0] % 4) * size, (tile->ids[0] / 4) * size, size, size});
	mlxe_draw_subtexture(game->window,
		game->assets.tilesets[(int)tile->tileset],
		(t_vector2){pos.x + size, pos.y},
		(t_rect){(tile->ids[1] % 4) * size, (tile->ids[1] / 4) * size, size, size});
	mlxe_draw_subtexture(game->window,
		game->assets.tilesets[(int)tile->tileset],
		(t_vector2){pos.x, pos.y + size},
		(t_rect){(tile->ids[2] % 4) * size, (tile->ids[2] / 4) * size, size, size});
	mlxe_draw_subtexture(game->window,
		game->assets.tilesets[(int)tile->tileset],
		(t_vector2){pos.x + size, pos.y + size},
		(t_rect){(tile->ids[3] % 4) * size, (tile->ids[3] / 4) * size, size, size});
}

void	draw_map(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			draw_tile(game, &game->map.grid[i][j], (t_vector2){j * TILE_SIZE, i * TILE_SIZE});
			j++;
		}
		i++;
	}
}
