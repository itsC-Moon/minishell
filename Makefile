# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 15:29:19 by hibenouk          #+#    #+#              #
#    Updated: 2024/03/20 13:28:20 by hibenouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT 	= $(shell find ./libft -type f -name "*.c")
SRC 	= $(shell find ./src -type f -name "*.c")
PARSER 	= $(shell find ./parsing -type f -name "*.c")
EXEC 	= $(shell find ./execution -type f -name "*.c")
BUILT 	= $(shell find ./builtin -type f -name "*.c")
INCL 	= $(shell find ./include -type f -name "*.c")


OBJ 	=	$(patsubst ./libft/%.c, ./obj/%.o, $(LIBFT)) 	$(patsubst ./src/%.c, ./obj/%.o, $(SRC)) \
			$(patsubst ./parsing/%.c, ./obj/%.o, $(PARSER)) $(patsubst ./execution/%.c, ./obj/%.o, $(EXEC))\
			$(patsubst ./builtin/%.c, ./obj/%.o, $(BUILT))
NAME = minishell

CC = cc

CFLAGS = -ggdb3 -Wall -Wextra -Wunreachable-code \
		 -I/Users/hibenouk/.brew/opt/readline/include \

INC = include

READLINE = -L/Users/hibenouk/.brew/opt/readline/lib
READINC = -I/Users/hibenouk/.brew/opt/readline/include

all : $(NAME) run

$(NAME) : $(OBJ)
	@$(CC)  $(CFLAGS) $(OBJ) $(READLINE) -lreadline  -I$(INC) -o $(NAME)

./obj/%.o : ./libft/%.c $(INCL)
	@$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

./obj/%.o : ./src/%.c $(INCL)
	@$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

./obj/%.o : ./parsing/%.c $(INCL)
	@$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

./obj/%.o : ./execution/%.c $(INCL)
	@$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

./obj/%.o : ./builtin/%.c $(INCL)
	@$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

run :
	@./$(NAME)
clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
re : fclean all
