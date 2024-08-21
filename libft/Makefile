# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 16:05:08 by lfarhi            #+#    #+#              #
#    Updated: 2024/07/08 18:01:13 by lfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ./
#SRCS = ${SRC}ft_atoi.c ${SRC}ft_bzero.c ${SRC}ft_calloc.c ${SRC}ft_isalnum.c ${SRC}ft_isalpha.c
#SRCS += ${SRC}ft_isascii.c ${SRC}ft_isdigit.c ${SRC}ft_isprint.c ${SRC}ft_memchr.c ${SRC}ft_memcmp.c
#SRCS += ${SRC}ft_memcpy.c ${SRC}ft_memmove.c ${SRC}ft_memset.c ${SRC}ft_strchr.c
#SRCS += ${SRC}ft_strlcat.c ${SRC}ft_strlcpy.c ${SRC}ft_strnstr.c
#SRCS += ${SRC}ft_strrchr.c ${SRC}ft_tolower.c ${SRC}ft_toupper.c

#SRCS += ${SRC}ft_substr.c ${SRC}ft_strjoin.c ${SRC}ft_strtrim.c ${SRC}ft_split.c ${SRC}ft_itoa.c
#SRCS += ${SRC}ft_strmapi.c ${SRC}ft_striteri.c

SRCS = ${SRC}ft_lstadd_back.c ${SRC}ft_lstadd_front.c ${SRC}ft_lstclear.c
SRCS += ${SRC}ft_lstdelone.c ${SRC}ft_lstiter.c ${SRC}ft_lstlast.c
SRCS += ${SRC}ft_lstmap.c ${SRC}ft_lstnew.c ${SRC}ft_lstsize.c
SRCS += ${SRC}ft_lstremove.c

SRCS += ${SRC}ft_strncmp.c 
SRCS += ${SRC}ft_strdup.c ${SRC}ft_putstr_fd.c ${SRC}ft_memcpy.c ${SRC}ft_strlen.c
SRCS += ${SRC}ft_putchar_fd.c ${SRC}ft_putendl_fd.c ${SRC}ft_putnbr_fd.c

SRCS += ${SRC}gnl/get_next_line.c
SRCS += ${SRC}gnl/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re