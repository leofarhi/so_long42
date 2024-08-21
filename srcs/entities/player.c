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

static t_entity	*check_player_hit(t_game *game)
{
	const t_vector2	dir[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int				i;
	t_list			*curr;
	t_entity		*entity;

	curr = game->map.entities;
	while (curr)
	{
		entity = (t_entity *)curr->content;
		if (entity->collidable)
		{
			i = 0;
			while (i < 4)
			{
				if (game->player->pos.x / TILE_SIZE + dir[i].x
					== entity->pos.x / TILE_SIZE
					&& game->player->pos.y / TILE_SIZE + dir[i].y
					== entity->pos.y / TILE_SIZE)
					return (entity);
				i++;
			}
		}
		curr = curr->next;
	}
	return (NULL);
}

static t_bool	move_check_collider(t_game *game,
	struct s_entity *entity, t_vector2 pos)
{
	t_entity	*collide;

	collide = check_player_hit(game);
	if (collide)
	{
		if (game->cadence.perfect)
		{
			collide = entities_collide(game, pos.x, pos.y);
			if (collide != NULL)
				collide->life--;
		}
		else
		{
			entity->life--;
			game->window->funct_ptr = flash_loop;
			return (TRUE);
		}
	}
	if (game->map.grid[pos.y][pos.x].tileset == 0)
	{
		collide = entities_collide(game, pos.x, pos.y);
		if (collide != NULL && collide != entity)
			return (TRUE);
	}
	return (FALSE);
}

static void	want_to_move(t_game *game, struct s_entity *entity, int x, int y)
{
	t_vector2	pos;

	entity->dir = (x == 1) * 2 + (x == -1) * 1 + (y == 1) * 0 + (y == -1) * 3;
	pos = (t_vector2){entity->pos.x / TILE_SIZE + x,
		entity->pos.y / TILE_SIZE + y};
	if (near_center(game))
		game->cadence.perfect = TRUE;
	if (move_check_collider(game, entity, pos))
		return ;
	if (game->map.grid[pos.y][pos.x].tileset == 0)
	{
		entity->lock_collide = (t_vector2){pos.x, pos.y};
		entity->anim_countdown = 6;
		game->step++;
		ft_putnbr_fd(game->step, 1);
		ft_putstr_fd(" steps\n", 1);
	}
	else if (!BONUS)
	{
		camera_goto(game, entity->pos, 1);
		camera_goto(game, (t_vector2){entity->pos.x + (x * TILE_SIZE),
			entity->pos.y + (y * TILE_SIZE)}, 3);
	}
}

static void	move_input(t_game *game, struct s_entity *entity)
{
	if (mlxe_is_key_down(game->window, XK_w)
		|| mlxe_is_key_down(game->window, XK_Up))
		want_to_move(game, entity, 0, -1);
	else if (mlxe_is_key_down(game->window, XK_s)
		|| mlxe_is_key_down(game->window, XK_Down))
		want_to_move(game, entity, 0, 1);
	else if (mlxe_is_key_down(game->window, XK_a)
		|| mlxe_is_key_down(game->window, XK_Left))
		want_to_move(game, entity, -1, 0);
	else if (mlxe_is_key_down(game->window, XK_d)
		|| mlxe_is_key_down(game->window, XK_Right))
		want_to_move(game, entity, 1, 0);
}

void	player_update(t_game *game, struct s_entity *entity)
{
	if (entity->life <= 0)
	{
		game->window->funct_ptr = gameover_loop;
	}
	if (!entity->anim_countdown)
	{
		move_input(game, entity);
		entity->sprite_idx = (entity->dir * 3) + 1;
	}
	if (entity->anim_countdown && game->sprite_update)
	{
		entity->anim_countdown--;
		entity->pos.x += ((entity->dir == 2) - (entity->dir == 1))
			* (TILE_SIZE / 6);
		entity->pos.y += ((entity->dir == 0) - (entity->dir == 3))
			* (TILE_SIZE / 6);
		entity->sprite_idx = (entity->dir * 3)
			+ ((6 - entity->anim_countdown) % 3);
	}
	camera_goto(game, entity->pos, 10);
}
