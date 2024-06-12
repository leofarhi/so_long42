/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:18:04 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 19:04:16 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

static void clear_garbage(void *ptr)
{
	t_garbage	*g;
	
	g = (t_garbage *)ptr;
	if (g->free)
		g->free(g->ptr);
}

void	mlxe_destroy(t_window *window)
{
	mlxe_free_garbage(window);
	mlx_destroy_image(window->mlx, window->buffer);
	mlx_destroy_window(window->mlx, window->win);
	free(window);
}
