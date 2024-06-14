/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:15:25 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 16:06:04 by lfarhi           ###   ########.fr       */
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
	mlxe_draw_texture(window, texture, 100-i, 0);
	mlxe_draw_texture(window, texture, 100, i);
	mlxe_draw_texture(window, texture, 100, 100-i);
	mlxe_draw_subtexture(window, texture, (t_vector2){200, 200}, (t_rect){20, 20, 100, 100});
	mlxe_draw_subtexture_size(window, texture, (t_coords){(t_rect){0, 0, 100, texture->size.y}, (t_rect){300, 300, 100, 100}}, 0x00FF00FF);
	i = (i + 1) % 800;
	mlxe_draw_line(window, (t_vector2){-100, 0}, (t_vector2){799+100, 599}, 0x00FF00FF);
	mlxe_render(window);
}

void loop_text(t_window *window, void *data)
{
	t_font		*font = (t_font *)data;
	static int	i = 0;
	(void)window;
	(void)font;

	mlxe_clear(window);
	mlxe_draw_text(window, font, "Hello, world!", (t_vector2){100, 100});
	mlxe_draw_text(window, font, "AB CDEF", (t_vector2){i, 300});
	mlxe_draw_text(window, font, "YAAA !", (t_vector2){200, i});
	mlxe_draw_text(window, font, "Woua !", (t_vector2){200, 100 - i});
	mlxe_draw_text(window, font, "\"hee ?", (t_vector2){100 - i, 200});
	i = (i + 1) % 800;
	mlxe_render(window);
}

void loop_sprite(t_window *window, void *data)
{
	t_sprite	*sprite = (t_sprite *)data;
	static int	i = 0;
	(void)window;
	(void)sprite;

	mlxe_clear(window);
	mlxe_draw_sprite(window, sprite, 100, 100);
	mlxe_draw_sprite(window, sprite, i, 300);
	mlxe_draw_sprite(window, sprite, 200, i);
	mlxe_draw_sprite(window, sprite, 200, 100 - i);
	mlxe_draw_sprite(window, sprite, 100 - i, 200);
	i = (i + 1) % 800;
	mlxe_render(window);
}


int	main(void)
{
	t_window	*window;

	window = mlxe_init(800, 600, "Hello, world!");
	if (!window)
		return (1);
	/*
	t_texture	*texture = mlxe_load_texture(window, "tests/test.xpm", TRUE);
	if (!texture)
	{
		printf("Failed to load texture\n");
		return (1);
	}
	
	mlxe_loop(window, loop, texture);//*/
	/*
	t_font	*font = mlxe_create_font(window, "tests/Triforce.xpm", TRUE);
	if (!font)
	{
		printf("Failed to load font\n");
		return (1);
	}
	mlxe_font_set_size(font, 90);
	mlxe_font_set_color(font, mlxe_color(255, 0, 0));
	mlxe_loop(window, loop_text, font);//*/
	//*
	t_texture	*texture = mlxe_load_texture(window, "tests/test.xpm", TRUE);
	t_sprite	*sprite = mlxe_create_sprite(window, texture, (t_rect){0, 0, 100, 100}, TRUE);
	mlxe_sprite_set_offset(sprite, (t_vector2){250, 50});
	mlxe_loop(window, loop_sprite, sprite);//*/
	
	mlxe_destroy(window);
	printf("Hello, world!\n");
	return (0);
}
