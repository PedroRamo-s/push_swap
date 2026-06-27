# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/14 14:51:25 by aantela-          #+#    #+#              #
#    Updated: 2026/06/27 06:36:19 by aantela-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -march=native -g
 

SRCS	= main_novo.c \
		  debug.c \
		  erro_handler.c \
		  parse_args.c \
		  parse_args_utils.c \
		  push_swap_utils.c \
		  push_swap_utils_medium.c \
		  bench.c \
		  bench_utils.c \
		  utils.c \
		  utils_1.c	\
		  push.c \
		  swap.c \
		  rotate.c \
		  reverse_rotate.c \
		  simple_sort.c \
		  medium_sort_teste.c \
		  complex_sort.c \
		  complex_sort_utils.c \
		  complex_sort_utils_1.c \
		  complex_sort_utils_2.c \
		  complex_sort_utils_3.c

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
