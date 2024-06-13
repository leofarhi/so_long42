/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:46:04 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 00:46:04 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static int get_width(t_font *font, char c)
{
    c = c - 32;
    return (font->widths[(int)c]);
}

static int get_start(t_font *font, char c)
{
    int i;
    int start;

    i = 0;
    start = 0;
    while (i < c - 32)
    {
        start += font->widths[i];
        i++;
    }
    return (start);
}

void	mlxe_draw_text(t_window *window, t_font *font, char *text, t_vector2 pos)
{
    int i;
    t_coords coords;

    i = 0;
    coords.dest = (t_rect){pos.x, pos.y, 0, 0};
    coords.src = (t_rect){0, 0, 0, 0};
    while (text[i])
    {
        if (text[i] >= 32 && text[i] < 127)
        {
            coords.src.width = get_width(font, text[i]);
            coords.src.height = font->texture->size.y;
            coords.src.x = get_start(font, text[i]);
            coords.src.y = 1;
            coords.dest.height = font->size;
            coords.dest.width = coords.src.width * font->size / (float)font->texture->size.y;
            mlxe_draw_subtexture_size(window, font->texture, coords, font->color);
            coords.dest.x += coords.dest.width;
        }
        i++;
    }
}
