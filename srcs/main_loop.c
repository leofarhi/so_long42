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

void	main_loop(t_window *window, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	game->sprite_update = sprite_update();
	mlxe_clear(window);
	entities_update(game);
	if (game->sprite_update)
		cadence_update(game);
	draw_map(game);
	sort_entities(game);
	draw_entities(game);
	draw_game_ui(game);
	if (BONUS)
		cadence_draw(game);
	mlxe_render(window);
}
