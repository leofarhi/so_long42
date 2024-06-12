/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:14:38 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:39:34 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

t_window	*mlxe_init(int width, int height, char *title)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		return (NULL);
	window->mlx = mlx_init();
	if (!window->mlx)
	{
		free(window);
		return (NULL);
	}
	window->win = mlx_new_window(window->mlx, width, height, title);
	if (!window->win)
	{
		free(window);
		return (NULL);
	}
	window->buffer = mlxe_create_texture(window, width, height, false);
	if (!window->buffer)
	{
		mlxe_free_texture(window, window->buffer);
		free(window);
		return (NULL);
	}
	window->garbage = NULL;
	window->running = false;
	return (window);
}
