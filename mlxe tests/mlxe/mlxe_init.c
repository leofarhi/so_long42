/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:14:38 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 16:18:48 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdio.h>

static int	handle_keydown(int keysym, t_window *data)
{
    if (keysym == XK_Escape)
		mlxe_loop_end(data);
	data->keys[keysym] = (data->keys[keysym] << 4) + STATE_ONDOWN;
	data->keys[keysym] &= 0xFFFF;
    return (0);
}

static int	handle_keyrelease(int keysym, t_window *data)
{
	data->keys[keysym] = (data->keys[keysym] << 4) + STATE_ONRELEASE;
    return (0);
}

static int handle_close(t_window *data)
{
	mlxe_loop_end(data);
	return (0);
}

//mouse button handling
static int	handle_mousedown(int button, int x, int y, t_window *data)
{
	data->mouse.x = x;
	data->mouse.y = y;
	handle_keydown(MAX_KEYS + button, data);
	return (0);
}

static int	handle_mouseup(int button, int x, int y, t_window *data)
{
	data->mouse.x = x;
	data->mouse.y = y;
	handle_keyrelease(MAX_KEYS + button, data);
	return (0);
}

static void	init_keys(t_window *window)
{
	int	i;

	i = 0;
	while (i < MAX_ALL_KEYS)
		window->keys[i++] = 0;
}


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
		mlx_destroy_display(window->mlx);
		free(window);
		return (NULL);
	}
	window->buffer = mlxe_create_texture(window, width, height, false);
	if (!window->buffer)
	{
		mlxe_free_texture(window, window->buffer);
		mlx_destroy_window(window->mlx, window->win);
		mlx_destroy_display(window->mlx);
		free(window);
		return (NULL);
	}
	window->garbage = NULL;
	window->running = false;
	mlx_do_key_autorepeatoff(window->mlx);
	init_keys(window);
	mlx_hook(window->win, KeyPress, KeyPressMask, &handle_keydown, window); /* ADDED */
    mlx_hook(window->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, window); /* CHANGED */
	mlx_hook(window->win, 17, 0, &handle_close, window); /* ADDED */
	mlx_mouse_hook(window->win, &handle_mousedown, window); /* ADDED */
	mlx_hook(window->win, ButtonRelease, ButtonReleaseMask, &handle_mouseup, window); /* ADDED */
	return (window);
}
