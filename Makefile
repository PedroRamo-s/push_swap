# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/14 14:51:25 by aantela-          #+#    #+#              #
#    Updated: 2026/06/17 05:43:30 by aantela-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -march=native
 

SRCS	= main_t.c \
		  debug.c \
		  erro_handler.c \
		  parse_args.c \
		  push_swap_utils.c \
		  push_swap_utils_medium.c \
		  bench.c \
		  utils.c \
		  utils_1.c	\
		  push.c \
		  swap.c \
		  rotate.c \
		  reverse_rotate.c \
		  medium_sort.c  \
		  simple_sort.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
