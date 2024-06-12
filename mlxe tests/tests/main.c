/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:15:25 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 00:29:52 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlxe.h>
#include <mlx.h>
#include <stdio.h>

void	loop(t_window *window, void *data)
{
	static int	i = 0;
	t_texture	*texture = (t_texture *)data;
	(void)window;
	(void)texture;

	mlxe_clear(window);
	mlxe_draw_texture(window, texture, i, 0);
	i = (i + 1) % 800;
	mlxe_draw_line(window, (vec2){-100, 0}, (vec2){799+100, 599}, 0x00FF00FF);
	mlxe_render(window);
}

int	main(void)
{
	t_window	*window;

	window = mlxe_init(800, 600, "Hello, world!");
	if (!window)
		return (1);
	t_texture	*texture = mlxe_load_texture(window, "tests/0.xpm", true);
	if (!texture)
	{
		printf("Failed to load texture\n");
		return (1);
	}
	mlxe_loop(window, loop, texture);
	mlxe_destroy(window);
	printf("Hello, world!\n");
	return (0);
}