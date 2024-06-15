/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chest.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:32:06 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/15 22:32:06 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	chest_update(t_game *game, t_entity *entity)
{
	if (entity->anim_countdown && game->sprite_update)
		entity->anim_countdown--;
	if (entity->life && game->player->pos.x == entity->pos.x && game->player->pos.y == entity->pos.y)
	{
		entity->life = 0;
		entity->anim_countdown = 6;
		game->map.collectible_countdown--;
	}
	
	if (entity->life == 1)
		entity->sprite_idx = 0;
	else
		entity->sprite_idx = 3 - (entity->anim_countdown / 2);
}