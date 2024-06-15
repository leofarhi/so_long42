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
	t_list	*curr;
	t_entity	*entity;

	curr = game->map.entities;
	while (curr)
	{
		entity = (t_entity *)curr->content;
		mlxe_draw_sprite(game->window, entity->sprites[entity->sprite_idx],
			entity->pos.x - game->map.cam.x,
			entity->pos.y - game->map.cam.y);
		curr = curr->next;
	}
}

void	entities_update(t_game *game)
{
	t_list	*curr;
	t_entity	*entity;

	curr = game->map.entities;
	while (curr)
	{
		entity = (t_entity *)curr->content;
		entity->update(game, entity);
		curr = curr->next;
	}
}

void	entities_clear(t_game *game)
{
	ft_lstclear(&game->map.entities, free);
}