/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_UI.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:41:09 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/15 18:41:09 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <math.h>

void	draw_text_outline(t_window *window,
	t_font *font, char *text, t_vector2 pos)
{
	t_color	color;
	const int	s = 1;

	color = font->color;
	mlxe_font_set_color(font, mlxe_color(0, 0, 0));
	mlxe_draw_text(window, font, text, (VEC2){pos.x - s, pos.y - s});
	mlxe_draw_text(window, font, text, (VEC2){pos.x + s, pos.y - s});
	mlxe_draw_text(window, font, text, (VEC2){pos.x - s, pos.y + s});
	mlxe_draw_text(window, font, text, (VEC2){pos.x + s, pos.y + 1});
	mlxe_font_set_color(font, color);
	mlxe_draw_text(window, font, text, pos);
}

static void draw_title(t_window *window, t_game *game, t_color color,t_vector2 offset)
{
	mlxe_font_set_size(game->assets.font, 100);
	mlxe_font_set_color(game->assets.font, color);
	draw_text_outline(window, game->assets.font, "Cadence", (VEC2){300 + offset.x, 100 + offset.y});
	mlxe_font_set_size(game->assets.font, 60);
	draw_text_outline(window, game->assets.font, "of", (VEC2){300 + offset.x, 220 + offset.y});
	mlxe_font_set_size(game->assets.font, 100);
	draw_text_outline(window, game->assets.font, "So Long", (VEC2){350 + offset.x, 200 + offset.y});
}

void	menu_loop(t_window *window, void *data)
{
	t_game	*game;
	static float i = 0;
	static t_color	color = 0;

	game = (t_game *)data;
	mlxe_clear(window);
	draw_map(game);
	draw_entities(game);
	mlxe_font_set_size(game->assets.font, 100);
	draw_title(window, game, 0, (VEC2){5, 5});
	draw_title(window, game, color, (VEC2){0, 0});
	mlxe_font_set_size(game->assets.font, 40);
	mlxe_font_set_color(game->assets.font, mlxe_color(255, 255, 255));
	draw_text_outline(window,game->assets.font,
		"Press right click to start", (VEC2){300, 420 + cos(i) * 5});
	i = fmod(i + 0.045, 2 * M_PI);
	color += 0x030000 * (color < 0xFF0000);
	mlxe_render(window);
	if (mlxe_is_key_pressed(window, MOUSE_RIGHT))
		window->funct_ptr = main_loop;
}
