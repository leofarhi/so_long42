/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_create_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:05:13 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 00:11:20 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

t_texture	*mlxe_create_texture(t_window *window, int width, int height, bool add_garbage)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->img = mlx_new_image(window->mlx, width, height);
	if (!texture->img)
	{
		free(texture);
		return (NULL);
	}
	texture->size.x = width;
	texture->size.y = height;
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(window->mlx, texture->img);
		free(texture);
		return (NULL);
	}
	if (add_garbage)
	{
		if (!mlxe_add_garbage(window, texture, mlxe_free_texture))
		{
			mlx_destroy_image(window->mlx, texture->img);
			free(texture);
			return (NULL);
		}
	}
	return (texture);
}
