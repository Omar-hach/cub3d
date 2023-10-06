# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/02 22:56:03 by ohachami          #+#    #+#              #
#    Updated: 2023/09/02 22:56:05 by ohachami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

HEADER = cub3d.h

CFLAGS = -Werror -Wall -Wextra #-fsanitize=address

GLFW = $(shell brew --prefix glfw)

FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"$(GLFW)/lib"

SRC = 	parsing/cub3d.c\
		draw/ft_drawer.c\
		draw/map_draw.c
#parsing/check_textures.c
#parsing/check_map.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a MLX42/libmlx42.a -I$() -lglfw

all:$(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
	make -C libft re

.PHONY: all clean fclean re
