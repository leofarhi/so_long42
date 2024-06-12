/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:51 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:39:51 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EXT_H
# define MLX_EXT_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

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

#define SUCCESS 1
#define FAILURE 0

typedef struct s_window t_window;

typedef struct s_rect
{
	int x;
	int y;
	int width;
	int height;
}				t_rect;

typedef struct s_vector2
{
	int x;
	int y;
}				t_vector2;

#define vec2 t_vector2

typedef struct s_texture
{
	void	*img;
	t_vector2 size;
	char	*addr;
    int		bits_per_pixel;
    int		size_line;
    int		endian;
}				t_texture;

typedef struct s_sprite
{
	t_texture *texture;
	t_rect	rect;
}				t_sprite;

typedef struct s_garbage
{
	void	*ptr;
	void	(*free)(t_window *, void *);
}				t_garbage;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_texture	*buffer;
	t_list	*garbage;
	bool		running;
}				t_window;

#define uint unsigned int
typedef unsigned int t_color;

/*
** mlxe_free - Free a pointer
** is used to free a pointer that was added to the garbage collector
** without using window parameter
*/
void	mlxe_free(t_window *window, void *ptr);

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
void		mlxe_loop(t_window *window, int (*funct_ptr)(t_window *));
void		mlxe_loop_end(t_window *window);

int			mlxe_color(int r, int g, int b);//done

void		mlxe_draw_pixel(t_texture *texture, int x, int y, t_color color);//done
t_color			mlxe_get_pixel(t_texture *texture, int x, int y);//done
void		mlxe_write_pixel(t_texture *texture, int x, int y, t_color color);//done
t_color			mlxe_read_pixel(t_texture *texture, int x, int y);//done

void		mlxe_draw_line(t_window *window, t_vector2 p1, t_vector2 p2, t_color color);
void		mlxe_draw_rect(t_window *window, t_rect rect, t_color color);//done
void		mlxe_draw_fillrect(t_window *window, t_rect rect, t_color color);//done

t_texture	*mlxe_create_texture(t_window *window, int width, int height, bool add_garbage);//done
t_texture	*mlxe_load_texture(t_window *window, char *path, bool add_garbage);//done
t_sprite	*mlxe_create_sprite(t_window *window, t_texture *texture, t_rect rect, bool add_garbage);//done

void		mlxe_free_texture(t_window *window, void *texture);//done
void		mlxe_free_sprite(t_sprite *sprite);//done

void		mlxe_draw_texture(t_window *window, t_texture *texture, int x, int y);//done
void		mlxe_draw_subtexture(t_window *window, t_texture *texture, int x, int y, t_rect rect);//done
void		mlxe_draw_sprite(t_window *window, t_sprite *sprite, int x, int y);//done

bool		mlxe_add_garbage(t_window *window, void *ptr, void (*free)(t_window *, void *));//done
void		mlxe_free_garbage(t_window *window);//done

#endif