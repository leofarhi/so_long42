/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_subtexture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:41:01 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:41:01 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static void	change_bounds(t_window *window, int *x, int *y, t_rect *rect, t_texture *texture)
{
	if (*x < 0)
	{
		rect->width += *x;
		rect->x -= *x;
		*x = 0;
	}
	if (*y < 0)
	{
		rect->height += *y;
		rect->y -= *y;
		*y = 0;
	}
	if (rect->x + rect->width > texture->size.x)
		rect->width = texture->size.x - rect->x;
	if (rect->y + rect->height > texture->size.y)
		rect->height = texture->size.y - rect->y;
	if (*x + rect->width > window->buffer->size.x)
		rect->width = window->buffer->size.x - *x;
}

void	mlxe_draw_subtexture(t_window *window, t_texture *texture, int x, int y, t_rect rect)
{
	int			i;
	int			j;
	t_color		color;

	change_bounds(window, &x, &y, &rect, texture);
	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			color = mlxe_read_pixel(texture, rect.x + j, rect.y + i);
			if (color != 0)
				mlxe_write_pixel(window->buffer, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
