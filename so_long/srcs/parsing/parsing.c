/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:35:16 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 13:27:12 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void free_grid(char **data, size_t height)
{
	size_t i;

	i = 0;
	while (i < height)
		free(data[i++]);
	free(data);
}

static int realloc_map(t_map *map,char ***data, size_t new_height)
{
	char	**new_map;
	size_t	i;

	new_map = malloc(sizeof(char *) * new_height);
	if (!new_map)
		print_error("Failed to realloc map");
	i = 0;
	while (i < map->height)
	{
		new_map[i] = (*data)[i];
		i++;
	}
	while (i < new_height)
	{
		new_map[i] = malloc(sizeof(char) * map->width);
		if (!new_map[i])
		{
			free_grid(new_map, i);
			return (print_error("Failed to realloc map"));
		}
		i++;
	}
	free(*data);
	*data = new_map;
	map->height = new_height;
	return (0);
}

int	parse_map(t_window *window, char *path)
{
	int		fd;
	char	*line;
	char 	**data;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("Failed to open map");
	line = get_next_line(fd);
	if (!line)
		print_error("Failed to read map");
	window->map.width = gnl_strlen(line);
	window->map.height = 1;
	data = malloc(sizeof(char *) * window->map.height);
	if (!data)
		print_error("Failed to malloc map");
	data[0] = line;
	while ((line = get_next_line(fd)))
	{
		if (gnl_strlen(line) != window->map.width)
		{
			free(line);
			return (print_error("Invalid map"));
		}
		realloc_map(&window->map, &data, window->map.height + 1);
		data[window->map.height - 1] = line;
	}
	load_map(window, data);
	free_grid(data, window->map.height);
	return (0);
}