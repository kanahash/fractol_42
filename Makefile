# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 04:28:45 by kanahash          #+#    #+#              #
#    Updated: 2025/04/19 11:46:44 by kanahash         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./

SRC = libft/ft_isdigit.c libft/ft_putendl_fd.c libft/ft_strncmp.c \
      src/fractol.c src/ft_atof.c src/init.c src/keyboad_operation.c src/mouse_operation.c \
      src/print_msg.c src/render.c src/validate.c

OBJ = $(SRC:.c=.o)

MLX_PATH = minilibx-linux/
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)$(MLX_NAME)

LIBX_FLAGS = -Lminilibx-linux/ -lmlx -lX11 -lXext -lm -O3

all: $(MLX) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBX_FLAGS) -o $(NAME)

$(MLX):
	make -C $(MLX_PATH)

clean:
	$(RM) $(OBJ)
	make -C $(MLX_PATH) clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
