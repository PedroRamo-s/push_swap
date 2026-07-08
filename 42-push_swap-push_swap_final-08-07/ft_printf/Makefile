# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/20 04:09:58 by aantela-          #+#    #+#              #
#    Updated: 2026/05/24 23:22:55 by aantela-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome da biblioteca 
NAME        = libftprintf.a

# Compilador e Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs 

# Caminhos e Ficheiros
SRC         = ft_printf.c \
			  ft_putchar.c \
			  ft_putstr.c \
			  ft_putnbr.c \
			  ft_puthex.c \
			  ft_putptr.c \
			  ft_putnbr_uns.c

OBJ         = $(SRC:.c=.o)

# Regras Principais 
all: $(NAME)

# Cria a libftprintf.a 
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

# Regra para compilar ficheiros objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regras de Limpeza 
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
