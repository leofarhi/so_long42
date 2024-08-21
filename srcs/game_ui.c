/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:27:58 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/16 13:27:58 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	draw_game_ui(t_game *game)
{
	char	step[13];
	int		i;

	itoa_stack(game->step, step);
	mlxe_font_set_color(game->assets.font, mlxe_color(255, 255, 255));
	mlxe_font_set_size(game->assets.font, 36);
	draw_text_outline(game->window, game->assets.font,
		step, (t_vector2){15, 50});
	i = 0;
	while (i < game->player->life)
		mlxe_draw_subtexture_size(game->window, game->assets.ui[0],
			(t_coords){(t_rect){0, 0,
			game->assets.ui[0]->size.x, game->assets.ui[0]->size.y},
			(t_rect){10 + ((i++) * (game->assets.ui[0]->size.x / 1.7f)), 10,
			game->assets.ui[0]->size.x / 2,
			game->assets.ui[0]->size.y / 2}}, 0xFFFFFFFF);
}

void	gameover_loop(t_window *window, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	mlxe_clear(window);
	mlxe_font_set_color(game->assets.font, mlxe_color(255, 0, 0));
	mlxe_font_set_size(game->assets.font, 90);
	draw_text_outline(window, game->assets.font,
		"Game Over!", (t_vector2){250, 200});
	mlxe_render(window);
}

void	flash_loop(t_window *window, void *data)
{
	static int	count = 0;
	t_game		*game;

	game = (t_game *)data;
	game->sprite_update = sprite_update();
	mlxe_clear(window);
	mlxe_draw_fillrect(game->window, (t_rect){0, 0,
		game->window->buffer->size.x, game->window->buffer->size.y},
		mlxe_color(255, 0, 0));
	mlxe_render(window);
	if (game->sprite_update)
	{
		count++;
		if (count > 5)
		{
			game->window->funct_ptr = main_loop;
			count = 0;
		}
	}
}
