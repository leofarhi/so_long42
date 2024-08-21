/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:16:44 by lfarhi            #+#    #+#             */
/*   Updated: 2024/07/08 17:43:20 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	aux_itoa_stack(long n, char *s, int i)
{
	long	nb;

	nb = n;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	nb = n;
	s[i] = '\0';
	while (nb > 0)
	{
		s[--i] = nb % 10 + '0';
		nb /= 10;
	}
}

void	itoa_stack(long n, char *s)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		n = -n;
	}
	if (n == 0)
	{
		s[i++] = '0';
		s[i] = '\0';
	}
	else
		aux_itoa_stack(n, s, i);
}

float	lerpf(float a, float b, float t)
{
	return (a + t * (b - a));
}

int	truemod(int a, int b)
{
	return ((a % b + b) % b);
}

int	randint(int min, int max)
{
	static unsigned int	seed;

	seed = 42;
	seed = 48271 * seed % 2147483647 - 44488 * seed / 2147483647;
	return (min + seed % (max - min + 1));
}
