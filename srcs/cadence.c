/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cadence.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:13:27 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/16 16:13:27 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	cadence_init(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		game->cadence.beats[i] = -i * 0.2f;
		i++;
	}
	game->cadence.perfect = FALSE;
}

void	cadence_update(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		game->cadence.beats[i] += 0.019f;
		if (game->cadence.beats[i] > 1.0f)
			game->cadence.beats[i] = 0.0f;
		i++;
	}
}

t_bool	near_center(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (game->cadence.beats[i] > 0.87f)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	draw_triforce(t_game *game, t_bool ncenter)
{
	t_vector2	size;

	if (ncenter)
		size = (t_vector2){game->assets.ui[1]->size.x / 2,
			game->assets.ui[1]->size.y / 2};
	else
	{
		size = (t_vector2){game->assets.ui[1]->size.x / 3,
			game->assets.ui[1]->size.y / 3};
		if (game->sprite_update)
			game->cadence.perfect = FALSE;
	}
	mlxe_draw_subtexture_size(game->window, game->assets.ui[1],
		(t_coords){(t_rect){0, 0, game->assets.ui[1]->size.x,
		game->assets.ui[1]->size.y}, (t_rect){(game->window->buffer->size.x
			/ 2) - size.x / 2, game->window->buffer->size.y - size.y - 10,
		size.x, size.y}}, 0xFFFFFFFF);
	if (game->cadence.perfect)
	{
		mlxe_font_set_color(game->assets.font, mlxe_color(255, 255, 255));
		mlxe_font_set_size(game->assets.font, 36);
		draw_text_outline(game->window, game->assets.font, "Perfect!",
			(t_vector2){(game->window->buffer->size.x / 2) - 50,
			game->window->buffer->size.y - 50});
	}
}

void	cadence_draw(t_game *game)
{
	int			i;
	t_vector2	size;
	t_bool		ncenter;

	ncenter = near_center(game);
	i = 0;
	size = game->window->buffer->size;
	mlxe_draw_line(game->window, (t_vector2){0, size.y - 38},
		(t_vector2){size.x, size.y - 38}, 0xFFFFFFFF);
	while (i < 5)
	{
		mlxe_draw_fillrect(game->window, (t_rect){
			lerpf(0, (size.x / 2), game->cadence.beats[i]),
			size.y - 50, 10, 25}, 0xFF00FFAA);
		mlxe_draw_fillrect(game->window, (t_rect){
			lerpf(size.x, (size.x / 2), game->cadence.beats[i]),
			size.y - 50, 10, 25}, 0xFF00FFAA);
		i++;
	}
	draw_triforce(game, ncenter);
}
