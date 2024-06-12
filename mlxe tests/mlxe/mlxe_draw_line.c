/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:24:21 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 00:24:21 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

void clip_line(t_vector2 *p1, t_vector2 *p2, int width, int height)
{
    float t0 = 0.0f;
    float t1 = 1.0f;
    float xdelta = p2->x - p1->x;
    float ydelta = p2->y - p1->y;

    // Liste de délimiteurs
    float p[] = {-xdelta, xdelta, -ydelta, ydelta};
    float q[] = {p1->x, width - 1 - p1->x, p1->y, height - 1 - p1->y};

    for (int i = 0; i < 4; i++)
    {
        if (p[i] == 0 && q[i] < 0)
            return; // Ligne complètement en dehors
        float r = q[i] / p[i];
        if (p[i] < 0)
        {
            if (r > t1)
                return;
            else if (r > t0)
                t0 = r;
        }
        else if (p[i] > 0)
        {
            if (r < t0)
                return;
            else if (r < t1)
                t1 = r;
        }
    }

    p2->x = p1->x + t1 * xdelta;
    p2->y = p1->y + t1 * ydelta;
    p1->x = p1->x + t0 * xdelta;
    p1->y = p1->y + t0 * ydelta;
}

void mlxe_draw_line(t_window *window, t_vector2 p1, t_vector2 p2, t_color color)
{
    // Ajuster p1 et p2 pour qu'ils soient dans les limites de la fenêtre
    clip_line(&p1, &p2, window->buffer->size.x, window->buffer->size.y);

    t_vector2 delta;
    t_vector2 sign;
    t_vector2 error;
    t_vector2 current;

    delta.x = abs(p2.x - p1.x);
    delta.y = abs(p2.y - p1.y);
    sign.x = p1.x < p2.x ? 1 : -1;
    sign.y = p1.y < p2.y ? 1 : -1;
    error.x = delta.x - delta.y;
    current = p1;
    while (current.x != p2.x || current.y != p2.y)
    {
        mlxe_write_pixel(window->buffer, current.x, current.y, color);
        if (current.x == p2.x && current.y == p2.y)
            break ;
        error.y = error.x * 2;
        if (error.y > -delta.y)
        {
            error.x -= delta.y;
            current.x += sign.x;
        }
        if (error.y < delta.x)
        {
            error.x += delta.x;
            current.y += sign.y;
        }
    }
}

