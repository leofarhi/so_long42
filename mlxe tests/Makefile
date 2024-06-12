# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 15:45:34 by lfarhi            #+#    #+#              #
#    Updated: 2024/06/12 18:56:13 by lfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test
SRC = tests/
SRCS = ${SRC}main.c 

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -L ./libft -I ./libft -lft
MLX_FLAGS = -L ./minilibx -I ./minilibx -lmlx -Imlx -lXext -lX11 -lm -lz
MLXE_FLAGS = -L ./mlxe -I ./mlxe -lmlxe
LFLAGS = ${MLXE_FLAGS} ${MLX_FLAGS} ${LIBFT_FLAGS}

all: ${NAME}

${NAME}: mlx libft mlxe ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LFLAGS} -o ${NAME}

bonus: all

mlx:
	@make -C minilibx

mlxe:
	@make -C mlxe

libft:
	@make -C libft

%.o: %.c
	${CC} ${CFLAGS} ${LFLAGS} -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}
	@make -C minilibx clean
	@make -C libft fclean
	@make -C mlxe fclean

re: fclean all

.PHONY: all clean fclean re bonus mlx libft mlxe