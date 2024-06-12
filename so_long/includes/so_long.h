/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:17:57 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 18:58:31 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../libft/get_next_line/get_next_line.h"

#include <stdio.h> //TODO Remove

typedef struct s_texture
{
	void	*img;
	int size[2];
}				t_texture;

typedef struct s_sprite
{
	t_texture *texture;
	int offset[2];
}				t_sprite;

#define MAX_TEXTURES 100
#define MAX_SPRITES 100
#define MAX_TYPES 2

#define TILE_SIZE 48

typedef struct s_tile
{
	int	textures[4];
	char	type;
}				t_tile;

typedef struct s_type
{
	int textures[20];
}				t_type;

typedef struct s_assets
{
	t_texture	*textures[MAX_TEXTURES];
	t_sprite	*sprites[MAX_SPRITES];
	t_type		types[MAX_TYPES];
	size_t		cltext;
	size_t		clsprt;
	size_t		cltype;

	size_t	st_end_sp;
	size_t	st_button_sp;
	size_t	st_player_sp;
	size_t	st_enemy_sp;

	size_t 	st_ui_nb;
	size_t 	st_ui_cadre;
	size_t 	st_ui_rythme;
}				t_assets;

typedef struct s_window t_window;

typedef struct s_entity
{
	size_t	pos[2];
	char	dir;
	char	type;
	char	life;
	size_t	st_sprite;
	size_t	current_sprite;
	float	anim;
	void	(*update)(struct s_entity *entity, struct s_window *window);
}				t_entity;


typedef struct s_map
{
	size_t		width;
	size_t		height;
	t_tile	**grid;
	size_t	cam[2];
	char		life;
	t_list *entities;
}				t_map;

enum {
	KEY_NONE = 0,
	KEY_DOWN = 1,
	KEY_UP = 2,
	KEY_RIGHT = 3,
	KEY_LEFT = 4,
};

#define RYTHME_MAX 150
#define RYTHME_ELAPSED 50

typedef struct s_window
{
	void	*mlx;
	void	*win;
	size_t	width;
	size_t	height;
	t_assets assets;
	t_map	map;
	int		key;
	int		step;
	int		rythme;
}				t_window;

int	print_error(char *msg);

int	load_texture(t_window *window, char *relative_path);
int	create_sprite(t_window *window, t_texture *texture, int offsetx, int offsety);
int	create_sprite_load(t_window *window, char *relative_path, int offsetx, int offsety);
void	sprite_draw(t_window *window, int index, int x, int y);
void	tile_draw(t_window *window, t_tile *tile, int x, int y);

int load_type(t_window *window, char *path);

int	load_assets(t_window *window);

int	main_loop(t_window *window);

int	parse_map(t_window *window, char *path);

void	draw_map(t_window *window);
int	load_map(t_window *window, char **grid);

int	spawn_entity(t_window *window, char type, size_t x, size_t y);
void free_entities(t_list *entities);
void update_entities(t_window *window);
void draw_entities(t_window *window);

int	key_hook(int keycode,t_window *window);

void	update_player(struct s_entity *entity, struct s_window *window);

#endif