/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:15:25 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 18:44:30 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlxe.h>
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>

void	loop(t_window *window, void *data)
{
	static int	i = 0;
	t_texture	*texture = (t_texture *)data;
	(void)window;
	(void)texture;

	if (is_key_down(window, XK_b))
		printf("B is down\n");
	if (is_key_pressed(window, XK_b))
		printf("B ");
	if (is_key_released(window, XK_b))
		printf("B is released\n");
	if (is_key_down(window, MOUSE_LEFT))
		printf("Left mouse button is down\n");
	printf("Mouse position: %d, %d\n", window->mouse.x, window->mouse.y);

	mlxe_clear(window);
	mlxe_draw_texture(window, texture, i, 0);
	mlxe_draw_texture(window, texture, i + 100, 0);
	mlxe_draw_subtexture(window, texture, (t_vector2){200, 200}, (t_rect){20, 20, 100, 100});
	i = (i + 1) % 800;
	mlxe_draw_line(window, (t_vector2){-100, 0}, (t_vector2){799+100, 599}, 0x00FF00FF);
	mlxe_render(window);
}


int	main(void)
{
	t_window	*window;

	window = mlxe_init(800, 600, "Hello, world!");
	if (!window)
		return (1);
	t_texture	*texture = mlxe_load_texture(window, "tests/test.xpm", TRUE);
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
