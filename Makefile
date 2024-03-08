# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 15:29:19 by hibenouk          #+#    #+#              #
#    Updated: 2024/03/08 17:17:05 by hibenouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT 	= $(shell find ./libft -type f -name "*.c")
SRC 	= $(shell find ./src -type f -name "*.c")
PARSER 	= $(shell find ./parsing -type f -name "*.c")
EXEC 	= $(shell find ./execution -type f -name "*.c")
BUILT 	= $(shell find ./builtin -type f -name "*.c")
INCL 	= $(shell find ./include -type f -name "*.c")

OBJ 	= $(LIBFT:.c=.o) $(SRC:.c=.o) $(PARSER:.c=.o) $(EXEC:.c=.o) $(BUILT:.c=.o)

NAME = minishell

CC = cc

CFLAGS = -ggdb3 -Wall -Wextra -Wunreachable-code -fsanitize=address 

INC = include


all : $(NAME)

$(NAME) : $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) -lreadline -I$(INC) -o $(NAME)

%.o : %.c $(INCL)
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
re : fclean all
