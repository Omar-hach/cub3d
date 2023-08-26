NAME = cub3d

CFLAGS =   MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm  -Wunreachable-code -Ofast 

PARSING = ./parsing/cub3d.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c


SRCS = $(PARSING) 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): 
	gcc parsing/*.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm  -Wunreachable-code -Ofast

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re