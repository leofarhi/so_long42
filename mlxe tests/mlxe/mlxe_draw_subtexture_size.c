/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_subtexture_size.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:55:39 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 23:55:39 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"


static void change_bounds(t_window *window, t_coords *coords, t_texture *texture)
{
	if (coords->dest.x < 0)
	{
		coords->src.width += coords->dest.x;
		coords->src.x -= coords->dest.x;
		coords->dest.x = 0;
	}
	if (coords->dest.y < 0)
	{
		coords->src.height += coords->dest.y;
		coords->src.y -= coords->dest.y;
		coords->dest.y = 0;
	}
	if (coords->src.x + coords->src.width > texture->size.x)
		coords->src.width = texture->size.x - coords->src.x;
	if (coords->src.y + coords->src.height > texture->size.y)
		coords->src.height = texture->size.y - coords->src.y;
	if (coords->dest.x + coords->src.width > window->buffer->size.x)
		coords->src.width = window->buffer->size.x - coords->dest.x;
	if (coords->dest.y + coords->src.height > window->buffer->size.y)
		coords->src.height = window->buffer->size.y - coords->dest.y;
}

static t_color mix_colors(t_color color1, t_color color2)
{
	t_rgb	rgb1;
	t_rgb	rgb2;
	t_rgb	rgb;

	rgb1 = mlxe_extract_rgb(color1);
	rgb2 = mlxe_extract_rgb(color2);
	rgb.r = (rgb1.r * rgb2.r) / 0xFF;
	rgb.g = (rgb1.g * rgb2.g) / 0xFF;
	rgb.b = (rgb1.b * rgb2.b) / 0xFF;
	return (mlxe_color(rgb.r, rgb.g, rgb.b));
}

void	mlxe_draw_subtexture_size(t_window *window,
			t_texture *texture, t_coords coords, t_color color)
{
	float	x_ratio = (float)coords.src.width / coords.dest.width;
	float	y_ratio = (float)coords.src.height / coords.dest.height;
	int		i;
	int		j;
	t_color	texture_color;

	change_bounds(window, &coords, texture);
	i = 0;
	while (i < coords.dest.height)
	{
		j = 0;
		while (j < coords.dest.width)
		{
			texture_color = mlxe_read_pixel(texture, coords.src.x + (j * x_ratio), coords.src.y + (i * y_ratio));
			if (!(texture_color & 0xFF000000))
			{
				texture_color = mix_colors(texture_color, color);
				mlxe_write_pixel(window->buffer, coords.dest.x + j, coords.dest.y + i, texture_color);
			}
			j++;
		}
		i++;
	}
}
