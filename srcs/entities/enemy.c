/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:48:24 by lfarhi            #+#    #+#             */
/*   Updated: 2024/08/20 12:56:24 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	want_to_move(t_game *game, struct s_entity *entity, int x, int y)
{
	t_entity	*collide;
	t_vector2	pos;

	if (x == 0 && y == 0)
		return ;
	entity->dir = (x == 1) * 2 + (x == -1) * 1 + (y == 1) * 0 + (y == -1) * 3;
	pos = (t_vector2){entity->pos.x / TILE_SIZE + x,
		entity->pos.y / TILE_SIZE + y};
	if (game->map.grid[pos.y][pos.x].tileset == 0)
	{
		collide = entities_collide(game, pos.x, pos.y);
		if (collide != NULL && collide != entity)
			return ;
		entity->lock_collide = (t_vector2){pos.x, pos.y};
		entity->anim_countdown = 6;
	}
}

static void	move(t_game *game, struct s_entity *entity)
{
	t_vector2	move;
	t_vector2	dir;

	move = move_to(game, entity->lock_collide, game->player->lock_collide);
	dir.x = (move.x > entity->lock_collide.x)
		- (move.x < entity->lock_collide.x);
	dir.y = (move.y > entity->lock_collide.y)
		- (move.y < entity->lock_collide.y);
	want_to_move(game, entity, dir.x, dir.y);
}

void	enemy_update(t_game *game, struct s_entity *entity)
{
	if (entity->life <= 0)
	{
		ft_lstremove(&game->map.entities, entity, free);
		return ;
	}
	if (!entity->anim_countdown && entity->update_countdown + 1 <= game->step)
	{
		move(game, entity);
		entity->sprite_idx = (entity->dir * 3) + 1;
		entity->update_countdown = game->step;
	}
	if (entity->anim_countdown && game->sprite_update)
	{
		entity->anim_countdown--;
		entity->pos.x += ((entity->dir == 2)
				- (entity->dir == 1)) * (TILE_SIZE / 6);
		entity->pos.y += ((entity->dir == 0)
				- (entity->dir == 3)) * (TILE_SIZE / 6);
		entity->sprite_idx = (entity->dir * 3)
			+ ((6 - entity->anim_countdown) % 3);
	}
}
