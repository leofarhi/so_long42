/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_create_font.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:26:39 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 00:26:39 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static int get_char_width(t_texture *txt, int start)
{
	int	width;
	int	i;
	t_color alpha;

	width = (mlxe_read_pixel(txt, start, 0) & 0xFF000000) == 0;
	i = start + width;
	while (i < txt->size.x)
	{
		alpha = mlxe_read_pixel(txt, i, 0) & 0xFF000000;
		if (!alpha)
			return (width);
		width++;
		i++;
	}
	return (width);
}

static void save_all_width(t_font *font)
{
	int		i;
	int		width;
	
	i = 0;
	width = 0;
	while (i < 127 - 32)
	{
		font->widths[i] = get_char_width(font->texture, width);
		width += font->widths[i];
		i++;
	}
}

t_font	*mlxe_create_font(t_window *window, char *path, t_bool add_garbage)
{
	t_font	*font;

	font = malloc(sizeof(t_font));
	if (!font)
		return (NULL);
	font->texture = mlxe_load_texture(window, path, FALSE);
	if (!font->texture)
	{
		free(font);
		return (NULL);
	}
	font->size = 32;
	font->color = mlxe_color(255, 255, 255);
	save_all_width(font);
	if (add_garbage)
		mlxe_add_garbage(window, font, (void (*)(t_window *, void *))mlxe_free_font);
	return (font);
}
