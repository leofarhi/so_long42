# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 16:08:55 by lfarhi            #+#    #+#              #
#    Updated: 2024/06/12 23:41:06 by lfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmlxe.a
SRC = ./
SRCS = ${SRC}mlxe_create_sprite.c ${SRC}mlxe_draw_line.c \
${SRC}mlxe_draw_sprite.c ${SRC}mlxe_free_sprite.c ${SRC}mlxe_loop_end.c \
${SRC}mlxe_add_garbage.c ${SRC}mlxe_create_texture.c \
${SRC}mlxe_draw_pixel.c ${SRC}mlxe_draw_subtexture.c ${SRC}mlxe_free_texture.c\
${SRC}mlxe_init.c ${SRC}mlxe_render.c ${SRC}mlxe_clear.c ${SRC}mlxe_destroy.c \
${SRC}mlxe_draw_texture.c ${SRC}mlxe_get_pixel.c ${SRC}mlxe_loop.c \
${SRC}mlxe_load_texture.c ${SRC}mlxe_update_input.c ${SRC}mlxe_color.c \
${SRC}mlxe_draw_fillrect.c ${SRC}mlxe_draw_rect.c ${SRC}mlxe_free_garbage.c \
${SRC}mlxe_read_pixel.c ${SRC}mlxe_write_pixel.c \

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -L ../libft -I ../libft -lft
MLX_FLAGS = -L ../minilibx -I ../minilibx -lmlx -Imlx -lXext -lX11 -lm -lz
LFLAGS = ${MLX_FLAGS} ${LIBFT_FLAGS}

all: ${NAME}

${NAME}: mlx libft ${OBJS}
	ar rcs ${NAME} ${OBJS}

mlx:
	@make -C ../minilibx

libft:
	@make -C ../libft

%.o: %.c
	${CC} ${CFLAGS} ${LFLAGS} -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re