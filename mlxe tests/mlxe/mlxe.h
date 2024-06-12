/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:51 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 17:50:52 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EXT_H
# define MLX_EXT_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../libft/libft.h"

/*
** WELCOME TO MiniLibX Extended
** This library is an extension of the MiniLibX library
** It provides additional features to the MiniLibX library
** such as sprites, textures, and garbage collection
*/

#ifndef true
# define true 1
#endif

#ifndef false
# define false 0
#endif

#ifndef bool
# define bool int
#endif

typedef struct s_texture
{
	void	*img;
	int size[2];
}				t_texture;

typedef struct s_sprite
{
	t_texture *texture;
	int rect[4];
}				t_sprite;

typedef struct s_garbage
{
	void	*ptr;
	void	(*free)(void *);
}				t_garbage;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	void	*buffer;
	t_list	*garbage;
}				t_window;

/*
** mlxe_init - Initialize a window with a specific width, height, and title
** mlxe_clear - Clear the window
** mlxe_render - Render the window
** mlxe_destroy - Destroy the window and free all resources
** mlxe_update_input - Update the input of the window

** mlxe_color - Create a color from RGB values

** mlxe_draw_pixel_w - Draw a pixel on the window, 
**			SAFE to use (Check if the pixel is inside the window)
** mlxe_get_pixel_w - Get the color of a pixel from a texture,
**			SAFE to use (Check if the pixel is inside the window)
** mlxe_write_pixel_w - Write a pixel to a texture,
**			UNSAFE to use (Does not check if the pixel is inside the window)
** mlxe_read_pixel_w - Read a pixel from a texture
**			UNSAFE to use (Does not check if the pixel is inside the window)

** mlxe_draw_pixel_t - Draw a pixel on a texture,
**			SAFE to use (Check if the pixel is inside the texture)
** mlxe_get_pixel_t - Get the color of a pixel from a texture,
**			SAFE to use (Check if the pixel is inside the texture)
** mlxe_write_pixel_t - Write a pixel to a texture,
**			UNSAFE to use (Does not check if the pixel is inside the texture)
** mlxe_read_pixel_t - Read a pixel from a texture
**			UNSAFE to use (Does not check if the pixel is inside the texture)

** mlxe_draw_line - Draw a line on the window
** mlxe_draw_rect - Draw a rectangle on the window
** mlxe_draw_fillrect - Draw a filled rectangle on the window

** mlxe_create_texture - Create a texture with a specific width and height
** mlxe_load_texture - Load a texture from a file
** mlxe_create_sprite - Create a sprite from a texture

** mlxe_free_texture - Free a texture
** mlxe_free_sprite - Free a sprite

** mlxe_draw_texture - Draw a texture on the window
** mlxe_draw_subtexture - Draw a texture on the window
							with a specific width and height
** mlxe_draw_sprite - Draw a sprite on the window

** mlxe_add_garbage - Add a pointer to the garbage collector
** 	returns true if the pointer is added successfully
** 	returns false if memory allocation fails
** mlxe_free_garbage - Free all pointers in the garbage collector
** 	returns true if all pointers are freed successfully
** 	returns false if memory allocation fails
*/
t_window	*mlxe_init(int width, int height, char *title);//done
void		mlxe_clear(t_window *window);//done
void		mlxe_render(t_window *window);//done
void		mlxe_destroy(t_window *window);//done
void		mlxe_update_input(t_window *window);//TODO

int			mlxe_color(int r, int g, int b);//done

void		mlxe_draw_pixel_w(t_window *window, int x, int y, int color);
int			mlxe_get_pixel_w(t_window *texture, int x, int y);
void		mlxe_write_pixel_w(t_window *texture, int x, int y, int color);
int			mlxe_read_pixel_w(t_window *texture, int x, int y);

void		mlxe_draw_pixel_t(t_texture *texture, int x, int y, int color);
int			mlxe_get_pixel_t(t_texture *texture, int x, int y);
void		mlxe_write_pixel_t(t_texture *texture, int x, int y, int color);
int			mlxe_read_pixel_t(t_texture *texture, int x, int y);

void		mlxe_draw_line(t_window *window, int x1, int y1, int x2, int y2, int color);
void		mlxe_draw_rect(t_window *window, int x, int y, int width, int height, int color);
void		mlxe_draw_fillrect(t_window *window, int x, int y, int width, int height, int color);

t_texture	*mlxe_create_texture(t_window *window, int width, int height, bool add_garbage);
t_texture	*mlxe_load_texture(t_window *window, char *path, bool add_garbage);
t_sprite	*mlxe_create_sprite(t_texture *texture, int x, int y, int width, int height, bool add_garbage);

void		mlxe_free_texture(t_texture *texture);
void		mlxe_free_sprite(t_sprite *sprite);

void		mlxe_draw_texture(t_window *window, t_texture *texture, int x, int y);
void		mlxe_draw_subtexture(t_window *window, t_texture *texture, int x, int y,
				int width, int height, int sx, int sy);
void		mlxe_draw_sprite(t_window *window, t_sprite *sprite, int x, int y);

bool		mlxe_add_garbage(t_window *window, void *ptr, void (*free)(void *));
bool		mlxe_free_garbage(t_window *window);

#endif