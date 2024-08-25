/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:25:08 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 19:25:08 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	print_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	if (msg)
	{
		ft_putendl_fd(msg, 2);
		free(msg);
	}
	return (1);
}

t_bool	set_error(t_game *game, char *msg)
{
	if (!game->error_msg)
		game->error_msg = ft_strdup(msg);
	return (FAILURE);
}

static void	init_game(t_game *game)
{
	game->sprite_update = FALSE;
	game->player = NULL;
	game->exit = NULL;
	game->step = 0;
	game->error_msg = NULL;
	game->map.grid = NULL;
	game->map.entities = NULL;
}

static t_bool	start_map(t_game *game, char *map_path)
{
	size_t	len;

	len = ft_strlen(map_path);
	if (len < 4 || ft_strncmp(map_path + len - 4, ".ber", 4))
		return (set_error(game, "Invalid map extension"));
	if (load_assets(game) && parse_map(game, map_path)
		&& map_checker(game))
	{
		sort_entities(game);
		camera_goto(game, game->player->pos, 1);
		mlxe_loop(game->window, menu_loop, game);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

int	main(int ac, char **av)
{
	t_bool		error;
	t_window	*window;
	t_game		game;

	if (ac != 2)
		return (print_error("Usage : ./so_long [map.ber]"));
	window = mlxe_init(1920 / 2, 1080 / 2, "so_long");
	if (!window)
		return (print_error("Failed to initialize window"));
	init_game(&game);
	game.window = window;
	cadence_init(&game);
	error = start_map(&game, av[1]);
	entities_clear(&game);
	free_map(&game);
	mlxe_destroy(window);
	if (!error)
		return (print_error(game.error_msg));
	return (0);
}
