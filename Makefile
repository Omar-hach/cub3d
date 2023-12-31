# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdouzi < mdouzi@student.1337.ma>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/02 22:56:03 by ohachami          #+#    #+#              #
#    Updated: 2023/11/15 12:05:43 by mdouzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_bonus = cub3D_bonus

CC = gcc

HEADER = cub3d.h

CFLAGS = -Werror -Wall -Wextra

GLFW = $(shell brew --prefix glfw)

FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"$(GLFW)/lib" -g -fsanitize=address

SRC = 	parsing/cub3d.c\
		parsing/get_element.c\
		parsing/get_map.c\
		parsing/read_file.c\
		draw/ft_drawer.c\
		draw/map_draw.c\
		draw/init_tools.c\
		parsing/check_map.c\
		draw/assets_draw.c\
		draw/put_textures.c\
		draw/raycasting.c

SRC_bonus = bonus/cub3d_bonus.c\
			draw/ft_drawer.c\
			draw/map_draw.c\
			draw/init_tools.c\
			parsing/check_map.c\
			draw/assets_draw.c\
			draw/put_textures.c\
			draw/raycasting.c

# parsing/check_textures.c
OBJ = $(SRC:.c=.o)

OBJ_bonus = $(SRC_bonus:.c=.o)

LIBFT = libft/libft.a MLX42/libmlx42.a -I$() -lglfw

all:$(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

bonus: $(NAME_bonus) 

$(NAME_bonus):$(OBJ) $(OBJ_bonus) $(HEADER)
	make -C ./libft
	$(CC) $(FLAGS) $(LIBFT) $(OBJ_bonus) -o $(NAME_bonus)
 
clean:
	make -C libft clean
	rm -f $(OBJ) $(OBJ_bonus)

fclean: clean
	make -C libft fclean
	rm -f $(NAME) $(NAME_bonus)

re: fclean all
	make -C libft re

.PHONY: all clean fclean re bonus
