/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:45:18 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 19:09:30 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int want_to_move(t_window *window, struct s_entity *entity, int x, int y)
{
	if (window->map.grid[entity->pos[1] + y][entity->pos[0] + x].type != '1')
	{
		entity->pos[0] += x;
		entity->pos[1] += y;
		return (1);
	}
	//window->key = KEY_NONE;
	return (0);
}

void	update_player(struct s_entity *entity, struct s_window *window)
{
	int		cursprite;

	if (entity->current_sprite % 3 == 0 && entity->anim == 0)
	{
		if (window->key == KEY_UP)
		{
			want_to_move(window, entity, 0, -1);
			entity->current_sprite = 9;
		}
		else if (window->key == KEY_DOWN)
		{
			want_to_move(window, entity, 0, 1);
			entity->current_sprite = 0;
		}
		else if (window->key == KEY_LEFT)
		{
			want_to_move(window, entity, -1, 0);
			entity->current_sprite = 4;
		}
		else if (window->key == KEY_RIGHT)
		{
			want_to_move(window, entity, 1, 0);
			entity->current_sprite = 7;
		}
	}
	else
	{
		entity->anim += 0.03f;
		cursprite = entity->current_sprite / 3;
		if (entity->anim >= 1)
		{
			entity->anim = 0;
			entity->current_sprite++;
		}
		if (entity->current_sprite % 3 == 0)
			entity->current_sprite = cursprite * 3;
	}
	if (window->key != KEY_NONE)
	{
		window->step++;
		entity->anim = 0.01f;
	}
	window->key = KEY_NONE;
}