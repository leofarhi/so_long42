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
	return (SUCCESS);
}
