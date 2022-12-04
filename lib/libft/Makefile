# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 19:18:14 by takira            #+#    #+#              #
#    Updated: 2022/11/29 07:57:33 by takira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

NAME		= libft.a

SRCS		= ft_strlen.c \
              	ft_strlen_ns.c \
				ft_strlcpy.c \
              	ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
              	ft_substr.c \
              	ft_strtrim.c \
              	ft_bzero.c \
              	ft_calloc.c \
              	ft_memset.c \

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			rm -f $(OBJS) $(BONUSOBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
