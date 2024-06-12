# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 15:45:34 by lfarhi            #+#    #+#              #
#    Updated: 2024/06/11 17:49:23 by lfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRC = srcs/
SRCS = ${SRC}main.c ${SRC}/map.c ${SRC}/window.c ${SRC}/asset/assets.c 
SRCS += ${SRC}/asset/image.c ${SRC}/parsing/parsing.c ${SRC}/asset/tileset.c
SRCS += ${SRC}entity.c ${SRC}input.c
SRCS += ${SRC}entities/player.c

LIBFT = libft/

SRCS += ${LIBFT}get_next_line/get_next_line.c
SRCS += ${LIBFT}get_next_line/get_next_line_utils.c

SRCS += ${LIBFT}ft_lstadd_back.c ${LIBFT}ft_lstadd_front.c#TODO remove if not needed
SRCS += ${LIBFT}ft_lstclear.c ${LIBFT}ft_lstdelone.c
SRCS += ${LIBFT}ft_lstiter.c ${LIBFT}ft_lstlast.c
SRCS += ${LIBFT}ft_lstmap.c ${LIBFT}ft_lstnew.c
SRCS += ${LIBFT}ft_lstsize.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3#TODO: remove -g3
MLX_FLAGS = -L ./minilibx -I ./minilibx -lmlx -Imlx -lXext -lX11 -lm -lz
LFLAGS = ${MLX_FLAGS}

all: ${NAME}

${NAME}: mlx ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LFLAGS} -o ${NAME}

mlx:
	@make -C minilibx

%.o: %.c
	${CC} ${CFLAGS} ${LFLAGS} -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus