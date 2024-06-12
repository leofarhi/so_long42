/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:15:25 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:38:17 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlxe.h>
#include <mlx.h>
#include <stdio.h>

int	loop(t_window *window)
{
	mlxe_clear(window);
	return (0);
}

int	main(void)
{
	t_window	*window;

	window = mlxe_init(800, 600, "Hello, world!");
	if (!window)
		return (1);
	mlxe_loop(window, loop);
	//mlxe_destroy(window);
	printf("Hello, world!\n");
	return (0);
}