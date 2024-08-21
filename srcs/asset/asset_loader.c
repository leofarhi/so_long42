/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:52:51 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 19:52:51 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static t_bool	load_basic(t_game *game)
{
	game->assets.tilesets[0] = mlxe_load_texture(game->window,
			"assets/map/ground.xpm", TRUE);
	game->assets.tilesets[1] = mlxe_load_texture(game->window,
			"assets/map/wall.xpm", TRUE);
	if (!game->assets.tilesets[0] || !game->assets.tilesets[1])
		return (set_error(game, "Error: Failed to load texture"));
	game->assets.font = mlxe_create_font(game->window,
			"assets/font/Triforce.xpm", TRUE);
	if (!game->assets.font)
		return (set_error(game, "Error: Failed to load font"));
	game->assets.ui[0] = mlxe_load_texture(game->window,
			"assets/ui/heart.xpm", TRUE);
	game->assets.ui[1] = mlxe_load_texture(game->window,
			"assets/ui/cadence_center.xpm", TRUE);
	if (!game->assets.ui[0] || !game->assets.ui[1])
		return (set_error(game, "Error: Failed to load texture"));
	return (SUCCESS);
}

static	t_bool	load_player(t_game *game)
{
	t_texture	*texture;
	size_t		i;

	texture = mlxe_load_texture(game->window,
			"assets/entities/player.xpm", TRUE);
	if (!texture)
		return (set_error(game, "Error: Failed to load texture"));
	i = 0;
	while (i < 12)
	{
		game->assets.player[i] = mlxe_create_sprite(game->window, texture,
				(t_rect){(i % 3) * 48, (i / 3) * 72, 48, 72}, TRUE);
		if (!game->assets.player[i])
			return (set_error(game, "Error: Failed to create sprite"));
		mlxe_sprite_set_offset(game->assets.player[i],
			(t_vector2){0, -(TILE_SIZE - TILE_SIZE / 4)});
		i++;
	}
	return (SUCCESS);
}

static	t_bool	load_monster(t_game *game)
{
	t_texture	*texture;
	size_t		i;

	texture = mlxe_load_texture(game->window,
			"assets/entities/monster.xpm", TRUE);
	if (!texture)
		return (set_error(game, "Error: Failed to load texture"));
	i = 0;
	while (i < 12)
	{
		game->assets.monster[i] = mlxe_create_sprite(game->window, texture,
				(t_rect){(i % 3) * 48, (i / 3) * 72, 48, 72}, TRUE);
		if (!game->assets.monster[i])
			return (set_error(game, "Error: Failed to create sprite"));
		mlxe_sprite_set_offset(game->assets.monster[i],
			(t_vector2){0, -(TILE_SIZE - TILE_SIZE / 4)});
		i++;
	}
	return (SUCCESS);
}

static t_bool	load_chest_and_exit(t_game *game)
{
	t_texture	*texture;
	size_t		i;

	texture = mlxe_load_texture(game->window,
			"assets/entities/chest.xpm", TRUE);
	if (!texture)
		return (set_error(game, "Error: Failed to load texture"));
	i = 0;
	while (i < 4)
	{
		game->assets.chest[i] = mlxe_create_sprite(game->window, texture,
				(t_rect){0, i * 48, 48, 48}, TRUE);
		if (!game->assets.chest[i])
			return (set_error(game, "Error: Failed to create sprite"));
		i++;
	}
	texture = mlxe_load_texture(game->window, "assets/entities/exit.xpm", TRUE);
	if (!texture)
		return (set_error(game, "Error: Failed to load texture"));
	game->assets.exit[0] = mlxe_create_sprite(game->window, texture,
			(t_rect){0 * 48, 0, 48, 48}, TRUE);
	game->assets.exit[1] = mlxe_create_sprite(game->window, texture,
			(t_rect){1 * 48, 0, 48, 48}, TRUE);
	return (SUCCESS);
}

t_bool	load_assets(t_game *game)
{
	return (load_basic(game) && load_player(game)
		&& load_monster(game) && load_chest_and_exit(game));
}
