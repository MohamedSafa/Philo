# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msafa <msafa@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/27 00:00:00 by msafa             #+#    #+#              #
#    Updated: 2025/11/27 19:06:42 by msafa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
INCLUDES = -I./includes

# Source files
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parsing.c \
       $(SRC_DIR)/dining.c \
       $(SRC_DIR)/dining_utils.c \
       $(SRC_DIR)/init_data.c \
       $(SRC_DIR)/monitor.c

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN) $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled: $<$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED) Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED) $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
