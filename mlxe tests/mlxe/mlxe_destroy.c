/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:18:04 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:41:54 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_destroy(t_window *window)
{
	if (window->running)
		mlxe_loop_end(window);
	mlxe_free_garbage(window);
	mlxe_free_texture(window, window->buffer);
	mlx_destroy_window(window->mlx, window->win);
	free(window);
}
