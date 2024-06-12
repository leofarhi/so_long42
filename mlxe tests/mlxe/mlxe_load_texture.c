/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_load_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:08:35 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 19:10:03 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

t_texture	*mlxe_load_texture(t_window *window, char *path, bool add_garbage)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(window->mlx, path, &texture->size[0], &texture->size[1]);
	if (!texture->img)
	{
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
