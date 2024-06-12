/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:25:58 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/11 18:31:07 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void load_map_asset(t_window *window)//TODO int return
{
	//TODO Check if the texture are loaded
	load_type(window, "assets/map/ground/grass/");
	load_type(window, "assets/map/wall/wall/");
}

static void load_sprite_player(t_window *window)//TODO int return
{
	//TODO Check if the texture are loaded
	int	st_sprite;

	st_sprite = create_sprite_load(window, "assets/player/0.xpm", 9, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/player/1.xpm", 9, 0);
	create_sprite_load(window, "assets/player/2.xpm", 9, 0);
	create_sprite_load(window, "assets/player/3.xpm", 9, 0);
	create_sprite_load(window, "assets/player/4.xpm", 9, 0);
	create_sprite_load(window, "assets/player/5.xpm", 9, 0);
	create_sprite_load(window, "assets/player/6.xpm", 9, 0);
	create_sprite_load(window, "assets/player/7.xpm", 9, 0);
	create_sprite_load(window, "assets/player/8.xpm", 9, 0);
	create_sprite_load(window, "assets/player/9.xpm", 9, 0);
	create_sprite_load(window, "assets/player/10.xpm", 9, 0);
	create_sprite_load(window, "assets/player/11.xpm", 9, 0);
	window->assets.st_player_sp = st_sprite;
	
}

static void load_sprite_bnt_end(t_window *window)//TODO int return
{
	//TODO Check if the texture are loaded
	int	st_sprite;

	st_sprite = create_sprite_load(window, "assets/buttom/disable.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/buttom/enable.xpm", 0, 0);
	create_sprite_load(window, "assets/out/close.xpm", 0, 0);
	create_sprite_load(window, "assets/out/open.xpm", 0, 0);
	window->assets.st_button_sp = st_sprite;
	window->assets.st_end_sp = st_sprite + 2;
	
}

static void load_sprite_ui(t_window *window)//TODO int return
{
	int	st_sprite;

	st_sprite = create_sprite_load(window, "assets/ui/0.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/1.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/2.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/3.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/4.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/5.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/6.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/7.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/8.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/9.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/cadre.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/mid1.xpm", 0, 0);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/mid2.xpm", 12, 12);//TODO Check if the texture are loaded
	create_sprite_load(window, "assets/ui/bar.xpm", 0, 0);//TODO Check if the texture are loaded
	
	window->assets.st_ui_nb = st_sprite;
	window->assets.st_ui_cadre = st_sprite + 10;
	window->assets.st_ui_rythme = st_sprite + 11;
}

int	load_assets(t_window *window)
{
	window->assets.cltext = 0;
	window->assets.clsprt = 0;
	window->assets.cltype = 0;
	load_map_asset(window);//TODO Check if the texture are loaded
	load_sprite_player(window);//TODO Check if the texture are loaded
	load_sprite_bnt_end(window);//TODO Check if the texture are loaded
	load_sprite_ui(window);//TODO Check if the texture are loaded
	printf("cltext: %ld\n", window->assets.cltext);
	printf("clsprt: %ld\n", window->assets.clsprt);
	printf("cltype: %ld\n", window->assets.cltype);
	return (0);
}