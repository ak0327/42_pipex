# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 10:22:24 by takira            #+#    #+#              #
#    Updated: 2022/12/04 10:22:24 by takira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP

ifdef WITH_TEST
	CFLAGS		+= -g -fsanitize=address -fsanitize=undefined -D LESKS
endif

LIBFT_DIR	= ./libft
#LIBFT_NAME	= lib.a
#LIBFT		= $(LIBFT_DIR)/$(LIBFT_NAME)
#
#INCLUDES	= -I $(LIBFT_DIR)
#LIBS_DIR	= -L (LIBFT_DIR)
#LIBS		= -lft

VPATH		= $(SRC_DIR)
SRC_DIR		= ./srcs
SRC			= main.c
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR		= ./objs
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
#OBJ			= $(SRCS:.c=.o)
#OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
DEPS		= $(OBJS:%.o=%.d)
#INCS		= ./include

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re: fclean all

test:
	make all WITH_TEST=1

norm:
	@norminette -v
	norminette $(SRC_DIR) $(LIBFT_DIR)

.PHONY:	all clean fclean re

-include		$(DEPS)

