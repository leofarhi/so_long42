# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 15:45:34 by lfarhi            #+#    #+#              #
#    Updated: 2024/06/15 23:04:12 by lfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRC = srcs/
SRCS = ${SRC}main.c ${SRC}main_loop.c ${SRC}map.c ${SRC}title_ui.c
SRCS += ${SRC}parsing/parsing.c ${SRC}parsing/map_loader.c
SRCS += ${SRC}asset/asset_loader.c
SRCS += ${SRC}entities/player.c ${SRC}entities/entities_loader.c
SRCS += ${SRC}entities/entities.c ${SRC}entities/chest.c
SRCS += ${SRC}entities/exit.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_FLAGS = -L ./libft -I ./libft -lft
MLX_FLAGS = -L ./minilibx -I ./minilibx -lmlx -Imlx -lXext -lX11 -lm -lz
MLXE_FLAGS = -L ./mlxe -I ./mlxe -lmlxe
LFLAGS = ${MLXE_FLAGS} ${MLX_FLAGS} ${LIBFT_FLAGS}

LIBFT = libft/libft.a
MINILIBX = minilibx/libmlx.a
MLXE = mlxe/libmlxe.a

all: ${NAME}

${NAME}: ${MINILIBX} ${LIBFT} ${MLXE} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LFLAGS} -o ${NAME}

bonus: all

${MINILIBX}:
	@make -C minilibx

${MLXE}:
	@make -C mlxe

${LIBFT}:
	@make -C libft

%.o: %.c
	${CC} ${CFLAGS} ${LFLAGS} -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS}
	@make -C minilibx clean
	@make -C libft clean
	@make -C mlxe clean

fclean: clean
	rm -f ${NAME}
	@make -C minilibx clean
	@make -C libft fclean
	@make -C mlxe fclean

re: fclean all

.PHONY: all clean fclean re bonus mlx libft mlxe