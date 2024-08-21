/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:48:04 by lfarhi            #+#    #+#             */
/*   Updated: 2024/07/04 17:54:54 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <time.h>

#ifdef BONUS

t_bool	sprite_update(void)
{
	static clock_t	last_time = 0;
	clock_t			current_time;

	current_time = clock();
	if ((double)(current_time - last_time) / CLOCKS_PER_SEC >= 0.03)
	{
		last_time = current_time;
		return (TRUE);
	}
	return (FALSE);
}
#else

t_bool	sprite_update(void)
{
	static int	i = 0;

	if (i >= 5)
	{
		i = 0;
		return (TRUE);
	}
	i++;
	return (FALSE);
}
#endif