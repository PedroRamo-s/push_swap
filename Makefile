# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/14 14:51:25 by aantela-          #+#    #+#              #
#    Updated: 2026/07/01 05:21:49 by aantela-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -march=native -g
PRINTF_DIR = ./ft_printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

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
		  mmedium_sort.c \
		  complex_sort.c \
		  complex_sort_utils.c \
		  complex_sort_utils_1.c \
		  complex_sort_utils_2.c \
		  complex_sort_utils_3.c \

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF_LIB) -o $(NAME)

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)
%.o: %.c
	$(CC) $(CFLAGS) -I$(PRINTF_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
