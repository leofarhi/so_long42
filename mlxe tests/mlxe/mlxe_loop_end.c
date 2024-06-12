/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_loop_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:40:33 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:40:33 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_loop_end(t_window *window)
{
	mlx_loop_end(window->mlx);
	window->running = false;
}
