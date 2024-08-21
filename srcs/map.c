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
		(t_rect){(tile->ids[0] % 4) * size,
		(tile->ids[0] / 4) * size, size, size});
	mlxe_draw_subtexture(game->window,
		game->assets.tilesets[(int)tile->tileset],
		(t_vector2){pos.x + size, pos.y},
		(t_rect){(tile->ids[1] % 4) * size,
		(tile->ids[1] / 4) * size, size, size});
	mlxe_draw_subtexture(game->window,
		game->assets.tilesets[(int)tile->tileset],
		(t_vector2){pos.x, pos.y + size},
		(t_rect){(tile->ids[2] % 4) * size,
		(tile->ids[2] / 4) * size, size, size});
	mlxe_draw_subtexture(game->window,
		game->assets.tilesets[(int)tile->tileset],
		(t_vector2){pos.x + size, pos.y + size},
		(t_rect){(tile->ids[3] % 4) * size,
		(tile->ids[3] / 4) * size, size, size});
}

static void	draw_background(t_game *game)
{
	int	i;
	int	j;

	i = -truemod(game->map.cam.y, TILE_SIZE) - TILE_SIZE;
	while (i < game->window->buffer->size.y)
	{
		j = -truemod(game->map.cam.x, TILE_SIZE) - TILE_SIZE;
		while (j < game->window->buffer->size.x)
		{
			mlxe_draw_subtexture(game->window,
				game->assets.tilesets[0],
				(t_vector2){j, i},
				(t_rect){(TILE_SIZE / 2), 3 * (TILE_SIZE / 2),
				TILE_SIZE, TILE_SIZE});
			j += TILE_SIZE;
		}
		i += TILE_SIZE;
	}
}

void	draw_map(t_game *game)
{
	size_t	i;
	size_t	j;

	draw_background(game);
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			draw_tile(game, &game->map.grid[i][j], (t_vector2){
				(j * TILE_SIZE) - game->map.cam.x,
				(i * TILE_SIZE) - game->map.cam.y
			});
			j++;
		}
		i++;
	}
}

void	camera_goto(t_game *game, t_vector2 pos, int smoothness)
{
	if (smoothness < 1)
		smoothness = 1;
	game->map.cam.x += (pos.x - game->map.cam.x
			- game->window->buffer->size.x / 2) / smoothness;
	game->map.cam.y += (pos.y - game->map.cam.y
			- game->window->buffer->size.y / 2) / smoothness;
}
