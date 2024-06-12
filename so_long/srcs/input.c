/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:36:55 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 17:54:07 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	key_hook(int keycode,t_window *window)
{
	if (keycode == 119 || keycode == 65362)
	{
		window->key = KEY_UP;
	}
	else if (keycode == 115 || keycode == 65364)
	{
		window->key = KEY_DOWN;
	}
	else if (keycode == 97 || keycode == 65361)
	{
		window->key = KEY_LEFT;
	}
	else if (keycode == 100 || keycode == 65363)
	{
		window->key = KEY_RIGHT;
	}
	else if (keycode == 65307)
	{
		mlx_destroy_window(window->mlx, window->win);
		exit(0);
	}
	return (0);
}