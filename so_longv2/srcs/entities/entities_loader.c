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

static t_bool	assign_entity(t_game *game, char c, t_entity *entity)
{
	if (c == 'P')
	{
		if (game->player)
		{
			print_error("Multiple players found");//TODO change to return (FALSE);
			return (FALSE);
		}
		game->player = entity;
		printf("Player\n");
		entity->sprites = game->assets.player;
		entity->life = 3;
		entity->update = player_update;
		return (TRUE);
	}
	if (c == 'C')
	{
		game->map.collectible_countdown++;
		printf("Chest\n");
		entity->sprites = game->assets.chest;
		entity->life = 1;
		entity->update = chest_update;
		return (TRUE);
	}
	if (c == 'E')
	{
		if (game->exit)
		{
			print_error("Multiple exits found");//TODO change to return (FALSE);
			return (FALSE);
		}
		printf("Exit\n");
		entity->sprites = game->assets.exit;
		entity->life = 1;
		entity->update = exit_update;
		game->exit = entity;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	spawn_entity(t_game *game, char c, int x, int y)
{
	t_entity	*entity;
	t_list		*new;

	entity = malloc(sizeof(t_entity));
	if (!entity)
		return (print_error("Failed to malloc entity"));//TODO change to return (FALSE);
	if (!assign_entity(game, c, entity))
	{
		free(entity);
		return (print_error("Failed to assign entity"));//TODO change to return (FALSE);
	}
	new = ft_lstnew(entity);
	if (!new)
	{
		free(entity);
		return (print_error("Failed to malloc entity"));//TODO change to return (FALSE);
	}
	entity->pos.x = x * TILE_SIZE;
	entity->pos.y = y * TILE_SIZE;
	entity->id = c;
	entity->dir = 0;
	entity->anim_countdown = 0;
	entity->sprite_idx = 0;
	if (c == 'P')
		ft_lstadd_back(&game->map.entities, new);
	else
		ft_lstadd_front(&game->map.entities, new);
	return (TRUE);
}