/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:05:39 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/15 18:05:39 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	want_to_move(t_game *game, struct s_entity *entity, int x, int y)
{
	if (x == 1)
		entity->dir = 2;
	else if (x == -1)
		entity->dir = 1;
	else if (y == 1)
		entity->dir = 0;
	else if (y == -1)
		entity->dir = 3;
	if (game->map.grid[entity->pos.y / TILE_SIZE + y][entity->pos.x / TILE_SIZE + x].tileset == 0)
	{
		entity->anim_countdown = 6;
	}
}

void	player_update(t_game *game, struct s_entity *entity)
{
	(void)game;
	(void)entity;
	//<X11/keysym.h>
	//printf("x: %d, y: %d\n", entity->pos.x, entity->pos.y);
	
	if (!entity->anim_countdown)
	{
		if (mlxe_is_key_down(game->window, XK_w) || mlxe_is_key_down(game->window, XK_Up))
			want_to_move(game, entity, 0, -1);
		else if (mlxe_is_key_down(game->window, XK_s) || mlxe_is_key_down(game->window, XK_Down))
			want_to_move(game, entity, 0, 1);
		else if (mlxe_is_key_down(game->window, XK_a) || mlxe_is_key_down(game->window, XK_Left))
			want_to_move(game, entity, -1, 0);
		else if (mlxe_is_key_down(game->window, XK_d) || mlxe_is_key_down(game->window, XK_Right))
			want_to_move(game, entity, 1, 0);
		entity->sprite_idx = (entity->dir*3) + 1;
	}
	if (entity->anim_countdown && game->sprite_update)
	{
		entity->anim_countdown--;
		entity->pos.x += ((entity->dir == 2) - (entity->dir == 1)) * (TILE_SIZE / 6);
		entity->pos.y += ((entity->dir == 0) - (entity->dir == 3)) * (TILE_SIZE / 6);
		entity->sprite_idx = (entity->dir*3) + ((6 - entity->anim_countdown)%3);
	}
	camera_goto(game, entity->pos, 10);
}
