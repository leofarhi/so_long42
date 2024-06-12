/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:18:00 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 11:04:48 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int interpole(int start, int end, int x, int max)
{
	return (start + (end - start) * x / max);
}

static void draw_ui(t_window *window)
{
	int i;
	int value;

	i = window->assets.sprites[window->assets.st_ui_cadre]->texture->size[0];
	sprite_draw(window, window->assets.st_ui_cadre, window->width - i, 0);
	i = window->assets.sprites[window->assets.st_ui_nb]->texture->size[0];
	value = window->step;
	if (value > 999)
		value = 999;
	sprite_draw(window, window->assets.st_ui_nb + value % 10, window->width - (i + 10), 15);
	sprite_draw(window, window->assets.st_ui_nb + (value / 10) % 10, window->width - (i * 2 + 10), 15);
	sprite_draw(window, window->assets.st_ui_nb + (value / 100), window->width - (i * 3 + 10), 15);
	i = window->assets.sprites[window->assets.st_ui_rythme]->texture->size[1];
	sprite_draw(window, window->assets.st_ui_rythme + 2, interpole(0, window->width / 2, window->rythme, RYTHME_MAX), window->height - (i / 1.25f));
	sprite_draw(window, window->assets.st_ui_rythme + 2, interpole(window->width - 20, window->width / 2, window->rythme, RYTHME_MAX), window->height - (i / 1.25f));
	sprite_draw(window, window->assets.st_ui_rythme + (window->rythme <= RYTHME_MAX - RYTHME_ELAPSED), (window->width / 2) - (i / 2), window->height - i);
	
}

int	main_loop(t_window *window)
{
	//mlx_clear_window(window->mlx, window->win);
	update_entities(window);
	draw_map(window);
	draw_entities(window);
	draw_ui(window);
	window->rythme++;
	if (window->rythme > RYTHME_MAX)
		window->rythme = 0;
	mlx_do_sync(window->mlx);
	//mlx_clear_window(window->mlx, window->win);
	return (0);
}
