/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tileset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:15:50 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 13:14:08 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	load_tile(t_window *window, char *path, int index)
{
	char nb[3];
	char *full_path;
	int	text1;
	
	nb[2] = '\0';
	nb[1] = (index % 10) + '0';
	nb[0] = (index / 10) + '0';
	full_path = malloc(sizeof(char) * (gnl_strlen(path) + 3 + 4 + 1));
	if (!full_path)
		return (-1);
	full_path[0] = '\0';
	ft_strcat(full_path, path);
	ft_strcat(full_path, nb);
	ft_strcat(full_path, ".xpm");
	text1 = load_texture(window, full_path);
	free(full_path);
	return (text1);
}

int load_type(t_window *window, char *path)
{
	int i;
	int text1;

	i = 0;
	while (i < 20)
	{
		text1 = load_tile(window, path, i);
		if (text1 == -1)
			return (1);
		window->assets.types[window->assets.cltype].textures[i++] = text1;
	}
	window->assets.cltype++;
	return (0);
}