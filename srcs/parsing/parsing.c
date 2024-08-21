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

static void	free_grid(char **data, size_t height)
{
	size_t	i;

	i = 0;
	while (i < height)
		free(data[i++]);
	free(data);
}

static t_bool	realloc_map(t_game *game, char ***data, size_t new_height)
{
	char	**new_map;
	size_t	i;

	new_map = malloc(sizeof(char *) * new_height);
	if (!new_map)
		return (set_error(game, "Failed to realloc map"));
	i = 0;
	while (i < game->map.height)
	{
		new_map[i] = (*data)[i];
		i++;
	}
	free(*data);
	*data = new_map;
	game->map.height = new_height;
	return (SUCCESS);
}

static	int	gnl_loop(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line != NULL);
}

static t_bool	parse_loop(t_game *game, int fd, char ***data)
{
	char	*line;

	while (gnl_loop(fd, &line))
	{
		if (gnl_strlen(line) != game->map.width)
		{
			free(line);
			free_grid(*data, game->map.height);
			return (set_error(game, "Invalid map size"));
		}
		if (!realloc_map(game, data, game->map.height + 1))
		{
			free(line);
			free_grid(*data, game->map.height);
			return (set_error(game, "Failed to realloc map"));
		}
		(*data)[game->map.height - 1] = line;
	}
	return (SUCCESS);
}

t_bool	parse_map(t_game *game, char *path)
{
	int		fd;
	char	*line;
	char	**data;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (set_error(game, "Failed to open map"));
	line = get_next_line(fd);
	if (!line)
		return (set_error(game, "Failed to read map"));
	game->map.width = gnl_strlen(line);
	game->map.height = 1;
	data = malloc(sizeof(char *) * game->map.height);
	if (!data)
		return (set_error(game, "Failed to malloc map"));
	data[0] = line;
	if (!parse_loop(game, fd, &data))
		return (FAILURE);
	if (!load_map(game, data))
	{
		free_grid(data, game->map.height);
		return (set_error(game, "Failed to load map"));
	}
	free_grid(data, game->map.height);
	return (SUCCESS);
}
