/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:12:07 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 18:41:51 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void draw_entities(t_window *window)
{
	t_list	*current;
	t_entity	*entity;

	current = window->map.entities;
	while (current)
	{
		entity = (t_entity *)current->content;
		sprite_draw(window, entity->st_sprite + entity->current_sprite,
		(entity->pos[0] * TILE_SIZE) + window->map.cam[0],
		(entity->pos[1] * TILE_SIZE) + window->map.cam[1]);
		current = current->next;
	}
}

void free_entities(t_list *entities)
{
	t_list	*current;
	t_entity	*entity;

	current = entities;
	while (current)
	{
		entity = (t_entity *)current->content;
		free(entity);
		current = current->next;
	}
	ft_lstclear(&entities, free);
}

void update_entities(t_window *window)
{
	t_list	*current;
	t_entity	*entity;

	current = window->map.entities;
	while (current)
	{
		entity = (t_entity *)current->content;
		entity->update(entity, window);
		current = current->next;
	}
}

static int setup_entity(t_window *window, char type, t_entity *entity)
{
	if (type == 'P')
	{
		entity->st_sprite = window->assets.st_player_sp;
		entity->update = update_player;
	}
	/*else if (type == 'E')
	{
		entity->st_sprite = window->assets.st_enemy_sp;
		entity->update = update_enemy;
	}*/
	else
		return (-1);
	return (0);
}

int	spawn_entity(t_window *window, char type, size_t x, size_t y)
{
	//TODO: Implement entity spawning
	t_entity	*entity;
	t_list		*new;

	entity = malloc(sizeof(t_entity));
	if (!entity)
		return (-1);
	entity->type = type;
	entity->pos[0] = x;
	entity->pos[1] = y;
	entity->current_sprite = 0;
	entity->anim = 0;
	entity->life = 4;
	if (setup_entity(window, type, entity) == -1)
	{
		free(entity);
		return (-1);
	}
	new = ft_lstnew(entity);
	if (!new)
	{
		free(entity);
		return (-1);
	}
	ft_lstadd_back(&window->map.entities, new);
	return (0);
}