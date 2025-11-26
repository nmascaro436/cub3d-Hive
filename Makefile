# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkorvenp <jkorvenp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 11:12:56 by nmascaro          #+#    #+#              #
#    Updated: 2025/11/26 16:16:43 by jkorvenp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.c src/parser/parse.c
.SECONDARY: $(OBJS)
OBJS = $(SRCS:.c=.o)
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -I$(MLX_DIR)/include
MLX_LINK_FLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR) -Iinclude

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@cmake -B $(MLX_DIR)/build $(MLX_DIR)
	@cmake --build $(MLX_DIR)/build

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX_LINK_FLAGS) $(LIBFT_LIB) -o $(NAME)
	@echo "cub3D executable created"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX_FLAGS) -c $< -o $@
	
clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re