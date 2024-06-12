/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_free_garbage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:02:46 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 19:04:23 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static void clear_garbage(void *ptr)
{
	t_garbage	*g;
	
	g = (t_garbage *)ptr;
	if (g->free)
		g->free(g->ptr);
	free(g);
}

void	mlxe_free_garbage(t_window *window)
{
	ft_lstclear(&window->garbage, clear_garbage);
}
