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

static void	itoa_stack(long n, char *s)
{
	long	i;
	long	nb;

	i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		n = -n;
	}
	if (n == 0)
	{
		s[i++] = '0';
		s[i] = '\0';
	}
	else
	{
		nb = n;
		while (nb > 0)
		{
			nb /= 10;
			i++;
		}
		nb = n;
		s[i] = '\0';
		while (nb > 0)
		{
			s[--i] = nb % 10 + '0';
			nb /= 10;
		}
	}
}

void	draw_game_ui(t_game *game)
{
	char	step[13];
	int		i;

	itoa_stack(game->step, step);
	mlxe_font_set_color(game->assets.font, mlxe_color(255, 255, 255));
	mlxe_font_set_size(game->assets.font, 36);
	draw_text_outline(game->window,game->assets.font, step, (VEC2){15, 50});
	i = 0;
	while (i < game->player->life)
		mlxe_draw_subtexture_size(game->window, game->assets.ui[0],
			(t_coords){(t_rect){0, 0,
			game->assets.ui[0]->size.x, game->assets.ui[0]->size.y},
			(t_rect){10 + ((i++) * (game->assets.ui[0]->size.x / 1.7f)), 10,
			game->assets.ui[0]->size.x/2,
			game->assets.ui[0]->size.y/2}}, 0xFFFFFFFF);
}