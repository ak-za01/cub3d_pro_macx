NAME = cub3D

CC = cc

CFLAGS  = -Wall -Werror -Wextra #-fsanitize=address -g

INC = ./mandatory/includes/cub3d.h

libft_DIR = ./mandatory/42_Libft
libft = $(libft_DIR)/libft.a

# SRC = mandatory/main.c mandatory/parsing/parsing.c mandatory/parsing/textures.c mandatory/parsing/color.c \
# 	  mandatory/parsing/map.c mandatory/parsing/map_v.c mandatory/parsing/utils.c

SRC = mandatory/main.c mandatory/parsing/utils.c mandatory/parsing/parsing.c mandatory/parsing/parsing_utils.c \
	  mandatory/parsing/textures.c mandatory/parsing/color.c mandatory/parsing/color_utils.c \
	  mandatory/parsing/map.c mandatory/parsing/map_utils.c mandatory/parsing/map_utils2.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
#	@make -C $(libft_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(libft)

%.o: %.c $(INC) $(libft_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
#	@make -C $(libft_DIR) clean
	rm -f $(OBJ)

fclean: clean
#	@make -C $(libft_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re