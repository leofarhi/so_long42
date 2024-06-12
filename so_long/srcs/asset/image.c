/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:24:31 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 13:50:11 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	load_texture(t_window *window, char *relative_path)
{
	t_texture	*texture;
	int			img_width;
	int			img_height;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (-1);
	texture->img = mlx_xpm_file_to_image(window->mlx, relative_path,
		&img_width, &img_height);
	if (!texture->img)
	{
		free(texture);
		return (-1);
	}
	texture->size[0] = img_width;
	texture->size[1] = img_height;
	window->assets.textures[window->assets.cltext] = texture;
	return (window->assets.cltext++);
}

int	create_sprite(t_window *window, t_texture *texture, int offsetx, int offsety)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		return (-1);
	sprite->texture = texture;
	sprite->offset[0] = offsetx;
	sprite->offset[1] = offsety;
	window->assets.sprites[window->assets.clsprt] = sprite;
	return (window->assets.clsprt++);
}

int	create_sprite_load(t_window *window, char *relative_path, int offsetx, int offsety)
{
	t_texture	*texture;
	int			sprite;

	texture = window->assets.textures[load_texture(window, relative_path)];
	if (!texture)
		return (-1);
	sprite = create_sprite(window, texture, offsetx, offsety);
	return (sprite);
}

void	sprite_draw(t_window *window, int index, int x, int y)
{
	t_sprite *sprite;

	sprite = window->assets.sprites[index];
	mlx_put_image_to_window(window->mlx, window->win,
		sprite->texture->img, sprite->offset[0] + x, sprite->offset[1] + y);
}

void	tile_draw(t_window *window, t_tile *tile, int x, int y)
{
	mlx_put_image_to_window(window->mlx, window->win,
		window->assets.textures[tile->textures[0]]->img, x, y);
	mlx_put_image_to_window(window->mlx, window->win,
		window->assets.textures[tile->textures[1]]->img, x + (TILE_SIZE / 2), y);
	mlx_put_image_to_window(window->mlx, window->win,
		window->assets.textures[tile->textures[2]]->img, x, y + (TILE_SIZE / 2));
	mlx_put_image_to_window(window->mlx, window->win,
		window->assets.textures[tile->textures[3]]->img, x + (TILE_SIZE / 2), y + (TILE_SIZE / 2));
}