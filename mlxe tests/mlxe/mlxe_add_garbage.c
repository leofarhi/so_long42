/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_add_garbage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:01:49 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 17:04:53 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

t_bool	mlxe_add_garbage(t_window *window,
			void *ptr, void (*free)(t_window *, void *))
{
	t_garbage	*g;

	g = malloc(sizeof(t_garbage));
	if (!g)
		return (FALSE);
	g->ptr = ptr;
	g->free = free;
	ft_lstadd_back(&window->garbage, ft_lstnew(g));
	return (TRUE);
}
