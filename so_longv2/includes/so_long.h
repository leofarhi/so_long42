/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:31:11 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 19:31:11 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <libft.h>
# include <mlxe.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include <stdio.h>//TODO: Remove this

# define VEC2 t_vector2

# define TILE_SIZE 48

typedef struct s_tile
{
	char	ids[4];
	char	tileset;
}				t_tile;

typedef struct s_assets
{
	t_texture	*tilesets[4];
	t_texture	*entities[4];
	t_font		*font;
}				t_assets;

typedef struct s_map
{
	size_t		width;
	size_t		height;
	t_tile		**grid;
	t_vector2	cam;
	t_list		*entities;
}				t_map;

typedef struct s_game
{
	t_window	*window;
	t_map		map;
	t_assets	assets;
}	t_game;

int		print_error(char *msg);
t_bool	parse_map(t_game *game, char *path);
void	menu_loop(t_window *window, void *data);
void	main_loop(t_window *window, void *data);
void	draw_map(t_game *game);
t_bool	load_map(t_game *game, char **grid);
t_bool	load_assets(t_game *game);
void	free_map(t_game *game);

#endif