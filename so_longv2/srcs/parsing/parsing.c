/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:40:25 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 19:40:25 by lfarhi           ###   ########.fr       */
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

static int realloc_map(t_map *map, char ***data, size_t new_height)
{
	char	**new_map;
	size_t	i;

	new_map = malloc(sizeof(char *) * new_height);
	if (!new_map)
		return print_error("Failed to realloc map");
	i = 0;
	while (i < map->height)
	{
		new_map[i] = (*data)[i];
		i++;
	}
	free(*data);
	*data = new_map;
	map->height = new_height;
	return (0);
}

t_bool	parse_map(t_game *game, char *path)
{
	int		fd;
	char	*line;
	char 	**data;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return print_error("Failed to open map");
	line = get_next_line(fd);
	if (!line)
		return print_error("Failed to read map");
	game->map.width = gnl_strlen(line);
	game->map.height = 1;
	data = malloc(sizeof(char *) * game->map.height);
	if (!data)
		return print_error("Failed to malloc map");//TODO: free line
	data[0] = line;
	while ((line = get_next_line(fd)))
	{
		if (gnl_strlen(line) != game->map.width)
		{
			free(line);
			free_grid(data, game->map.height);
			return (print_error("Invalid map"));
		}
		realloc_map(&game->map, &data, game->map.height + 1);
		data[game->map.height - 1] = line;
	}
	load_map(game, data);
	free_grid(data, game->map.height);
	return (0);
}
