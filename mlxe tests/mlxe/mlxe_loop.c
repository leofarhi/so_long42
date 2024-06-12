/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:34:02 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:34:02 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_loop(t_window *window, int (*funct_ptr)(t_window *))
{
	mlx_loop_hook(window->mlx, funct_ptr, window);
	mlx_loop(window->mlx);
	window->running = true;
}
