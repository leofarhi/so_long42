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
# include <limits.h>

# define TILE_SIZE 48

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_game	t_game;

typedef struct s_tile
{
	char	ids[4];
	char	tileset;
	int		path_f;
}				t_tile;

typedef struct s_assets
{
	t_texture	*tilesets[4];
	t_sprite	*player[12];
	t_sprite	*monster[12];
	t_sprite	*chest[4];
	t_sprite	*exit[2];
	t_texture	*ui[2];
	t_font		*font;
}				t_assets;

typedef struct s_entity
{
	t_sprite	**sprites;
	int			sprite_idx;
	char		id;
	char		life;
	char		dir;
	t_vector2	pos;
	char		anim_countdown;
	void		(*update)(t_game *game, struct s_entity *entity);
	t_bool		collidable;
	t_vector2	lock_collide;
	int			update_countdown;
}				t_entity;

typedef struct s_cadence
{
	float		beats[5];
	t_bool		perfect;
}				t_cadence;

typedef struct s_map
{
	size_t		width;
	size_t		height;
	t_tile		**grid;
	t_vector2	cam;
	t_list		*entities;
	int			collectible_countdown;
}				t_map;

typedef struct s_game
{
	t_window	*window;
	t_map		map;
	t_assets	assets;
	t_entity	*player;
	t_entity	*exit;
	t_bool		sprite_update;
	int			step;
	t_cadence	cadence;
	char		*error_msg;
}	t_game;

int			print_error(char *msg);
t_bool		set_error(t_game *game, char *msg);
t_bool		parse_map(t_game *game, char *path);
void		menu_loop(t_window *window, void *data);
void		main_loop(t_window *window, void *data);
void		draw_map(t_game *game);
t_bool		load_map(t_game *game, char **grid);
t_bool		load_assets(t_game *game);
void		free_map(t_game *game);

t_bool		sprite_update(void);

t_bool		spawn_entity(t_game *game, char c, int x, int y);
void		player_update(t_game *game, struct s_entity *entity);
void		chest_update(t_game *game, t_entity *entity);
void		enemy_update(t_game *game, struct s_entity *entity);
void		exit_update(t_game *game, t_entity *entity);
void		entities_clear(t_game *game);
void		draw_entities(t_game *game);
void		entities_update(t_game *game);
t_entity	*entities_collide(t_game *game, int x, int y);
void		sort_entities(t_game *game);
void		camera_goto(t_game *game, t_vector2 pos, int smoothness);

int			truemod(int a, int b);
int			randint(int min, int max);
void		itoa_stack(long n, char *s);
float		lerpf(float a, float b, float t);

void		draw_text_outline(t_window *window,
				t_font *font, char *text, t_vector2 pos);

void		draw_game_ui(t_game *game);
void		gameover_loop(t_window *window, void *data);
void		flash_loop(t_window *window, void *data);

void		cadence_init(t_game *game);
void		cadence_update(t_game *game);
void		cadence_draw(t_game *game);
t_bool		near_center(t_game *game);

t_vector2	move_to(t_game *game, t_vector2 pos, t_vector2 dest);
t_bool		exists_path(t_game *game, t_vector2 pos, t_vector2 dest);
void		eset_path(t_game *game);

t_bool		map_checker(t_game *game);

void		update_tiles(t_game *game);

#endif