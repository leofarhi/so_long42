/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:05:26 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/15 18:05:26 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static t_bool	assign_entity_ext(t_game *game, char c, t_entity *entity)
{
	if (c == 'E')
	{
		if (game->exit)
			return (set_error(game, "Multiple exits found"));
		entity->sprites = game->assets.exit;
		entity->life = 1;
		entity->update = exit_update;
		game->exit = entity;
	}
	else if (c == 'M' && BONUS)
	{
		entity->sprites = game->assets.monster;
		entity->life = 3;
		entity->update = enemy_update;
		entity->sprite_idx = 1;
		entity->collidable = TRUE;
	}
	else
		return (set_error(game, "Invalid entity"));
	return (SUCCESS);
}

static t_bool	assign_entity(t_game *game, char c, t_entity *entity)
{
	if (c == 'P')
	{
		if (game->player)
			return (set_error(game, "Multiple players found"));
		game->player = entity;
		entity->sprites = game->assets.player;
		entity->life = 3;
		entity->update = player_update;
		entity->sprite_idx = 1;
		entity->collidable = TRUE;
	}
	else if (c == 'C')
	{
		game->map.collectible_countdown++;
		entity->sprites = game->assets.chest;
		entity->life = 1;
		entity->update = chest_update;
	}
	else if (!assign_entity_ext(game, c, entity))
		return (FAILURE);
	return (SUCCESS);
}

static void	init_entity(t_entity *entity, char c, t_vector2 pos)
{
	entity->pos.x = pos.x * TILE_SIZE;
	entity->pos.y = pos.y * TILE_SIZE;
	entity->lock_collide = pos;
	entity->id = c;
	entity->dir = 0;
	entity->anim_countdown = 0;
	entity->sprite_idx = 0;
	entity->collidable = FALSE;
	entity->update_countdown = 0;
}

t_bool	spawn_entity(t_game *game, char c, int x, int y)
{
	t_entity	*entity;
	t_list		*new;

	entity = malloc(sizeof(t_entity));
	if (!entity)
		return (set_error(game, "Failed to malloc entity"));
	init_entity(entity, c, (t_vector2){x, y});
	if (!assign_entity(game, c, entity))
	{
		free(entity);
		return (set_error(game, "Failed to assign entity"));
	}
	new = ft_lstnew(entity);
	if (!new)
	{
		free(entity);
		return (set_error(game, "Failed to malloc entity"));
	}
	ft_lstadd_front(&game->map.entities, new);
	return (SUCCESS);
}
