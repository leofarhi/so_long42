/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:53:13 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/15 18:53:13 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	draw_entities(t_game *game)
{
	t_list		*curr;
	t_entity	*entity;
	t_rect		rect;

	curr = game->map.entities;
	while (curr)
	{
		entity = (t_entity *)curr->content;
		mlxe_draw_sprite(game->window, entity->sprites[entity->sprite_idx],
			entity->pos.x - game->map.cam.x,
			entity->pos.y - game->map.cam.y);
		if (entity->id == 'M')
		{
			rect = (t_rect){entity->pos.x - game->map.cam.x + 10,
				entity->pos.y - game->map.cam.y
				+ entity->sprites[entity->sprite_idx]->offset.y - 10, 32, 5};
			mlxe_draw_fillrect(game->window, rect, 0x000000);
			rect.width *= (float)entity->life / 3.0f;
			mlxe_draw_fillrect(game->window, rect, mlxe_color(255, 0, 0));
		}
		curr = curr->next;
	}
}

void	entities_update(t_game *game)
{
	t_list		*curr;
	t_list		*next;
	t_entity	*entity;

	curr = game->map.entities;
	while (curr)
	{
		entity = (t_entity *)curr->content;
		next = curr->next;
		entity->update(game, entity);
		curr = next;
	}
}

void	entities_clear(t_game *game)
{
	if (game->map.entities)
		ft_lstclear(&game->map.entities, free);
}

t_entity	*entities_collide(t_game *game, int x, int y)
{
	t_list		*curr;
	t_entity	*entity;

	curr = game->map.entities;
	while (curr)
	{
		entity = (t_entity *)curr->content;
		if (entity->lock_collide.x == x
			&& entity->lock_collide.y == y && entity->collidable)
			return (entity);
		curr = curr->next;
	}
	return (NULL);
}

void	sort_entities(t_game *game)
{
	t_list		*lst[2];
	t_entity	*entity;

	lst[0] = game->map.entities;
	while (lst[0])
	{
		lst[1] = lst[0]->next;
		while (lst[1])
		{
			entity = (t_entity *)lst[0]->content;
			if (entity->pos.y > ((t_entity *)lst[1]->content)->pos.y)
			{
				lst[0]->content = lst[1]->content;
				lst[1]->content = entity;
			}
			else if (entity->pos.y == ((t_entity *)lst[1]->content)->pos.y
				&& (entity == game->player || entity->id == 'M'))
			{
				lst[0]->content = lst[1]->content;
				lst[1]->content = entity;
			}
			lst[1] = lst[1]->next;
		}
		lst[0] = lst[0]->next;
	}
}
