/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:28:14 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 19:28:14 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_bool	sprite_update()
{
	static int i = 0;

	if (i >= 5)
	{
		i = 0;
		return (TRUE);
	}
	i++;
	return (FALSE);
}

void main_loop(t_window *window, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	game->sprite_update = sprite_update();
	mlxe_clear(window);
	entities_update(game);
	cadence_update(game);
	draw_map(game);
	draw_entities(game);
	draw_game_ui(game);
	cadence_draw(game);
	mlxe_render(window);
}
