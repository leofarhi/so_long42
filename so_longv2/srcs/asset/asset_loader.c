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

t_bool	load_assets(t_game *game)
{
	game->assets.tilesets[0] = mlxe_load_texture(game->window, "assets/map/ground.xpm", TRUE);//TODO Check if loading is successful
	if (!game->assets.tilesets[0])
		printf("Error: Failed to load texture\n");//TODO remove this line
	game->assets.tilesets[1] = mlxe_load_texture(game->window, "assets/map/wall.xpm", TRUE);
	printf("tileset[0]: %p\n", game->assets.tilesets[0]);//TODO remove this line
	printf("tileset[1]: %p\n", game->assets.tilesets[1]);//TODO remove this line

	game->assets.font = mlxe_create_font(game->window, "assets/font/Triforce.xpm", TRUE);
	printf("font: %p\n", game->assets.font);//TODO remove this line

	//Player:
	t_texture	*player_texture;
	player_texture = mlxe_load_texture(game->window, "assets/entities/player.xpm", TRUE);//TODO Check if loading is successful
	printf("player_texture: %p\n", player_texture);//TODO remove this line
	for (int i = 0; i < 12; i++)
	{
		game->assets.player[i] = mlxe_create_sprite(game->window, player_texture, (t_rect){(i%3) * 48, (i/3) * 72, 48, 72}, TRUE);
		mlxe_sprite_set_offset(game->assets.player[i], (t_vector2){0, -(TILE_SIZE - TILE_SIZE/4)});
		printf("player[%d]: %p\n", i, game->assets.player[i]);//TODO remove this line
	}

	//Chest:
	t_texture	*chest_texture;
	chest_texture = mlxe_load_texture(game->window, "assets/entities/chest.xpm", TRUE);//TODO Check if loading is successful
	printf("chest_texture: %p\n", chest_texture);//TODO remove this line
	for (int i = 0; i < 4; i++)
	{
		game->assets.chest[i] = mlxe_create_sprite(game->window, chest_texture, (t_rect){0, i * 48, 48, 48}, TRUE);
		printf("chest[%d]: %p\n", i, game->assets.chest[i]);//TODO remove this line
	}

	//Exit:
	t_texture	*exit_texture;
	exit_texture = mlxe_load_texture(game->window, "assets/entities/exit.xpm", TRUE);//TODO Check if loading is successful
	printf("exit_texture: %p\n", exit_texture);//TODO remove this line
	for (int i = 0; i < 2; i++)
	{
		game->assets.exit[i] = mlxe_create_sprite(game->window, exit_texture, (t_rect){i * 48, 0, 48, 48}, TRUE);
		printf("exit[%d]: %p\n", i, game->assets.exit[i]);//TODO remove this line
	}
	return (SUCCESS);
}
