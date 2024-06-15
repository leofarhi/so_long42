/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:03:51 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/15 23:03:51 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	exit_loop(t_window *window, void *data)
{
	static int i = 0;
	t_game	*game;

	game = (t_game *)data;
	game->sprite_update = sprite_update();
	mlxe_clear(window);
	camera_goto(game, game->exit->pos, 30);
	if (game->sprite_update)
	{
		i++;
		if (i > 20)
			game->exit->sprites[0]->rect.width /= 1.1f;
		if (i > 60)
			game->window->funct_ptr = main_loop;
	}
	draw_map(game);
	draw_entities(game);
	mlxe_draw_sprite(game->window, game->exit->sprites[0],
			game->exit->pos.x - game->map.cam.x,
			game->exit->pos.y - game->map.cam.y);
	mlxe_render(window);
}

void	quit_loop(t_window *window, void *data)
{
	static int i = 0;
	t_game	*game;

	game = (t_game *)data;
	mlxe_clear(window);
	draw_map(game);
	draw_entities(game);
	if (i < game->window->buffer->size.x + 400)
		i += 10;
	else
		mlxe_loop_end(window);
	mlxe_draw_fillrect(game->window, (t_rect){0, 0,
	i, game->window->buffer->size.y}, 0);
	mlxe_font_set_color(game->assets.font, mlxe_color(255, 255, 255));
	mlxe_font_set_size(game->assets.font, 90);
	draw_text_outline(window,game->assets.font,
		"Congratulations!", (VEC2){200, 250});
	mlxe_render(window);
}

void	exit_update(t_game *game, t_entity *entity)
{
	if (game->map.collectible_countdown == 0 && game->player->pos.x == entity->pos.x && game->player->pos.y == entity->pos.y)
	{
		game->window->funct_ptr = quit_loop;
	}
	if (entity->sprite_idx == game->map.collectible_countdown)
		game->window->funct_ptr = exit_loop;
	entity->sprite_idx = game->map.collectible_countdown == 0;
}