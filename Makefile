

LIBFT 	= $(shell find ./libft -type f -name "*.c")
SRC 	= $(shell find ./src -type f -name "*.c")
PARSER 	= $(shell find ./parsing -type f -name "*.c")
EXEC 	= $(shell find ./execution -type f -name "*.c")
BUILT 	= $(shell find ./builtin -type f -name "*.c")
INCL 	= $(shell find ./include -type f -name "*.h")

OBJ 	=	$(patsubst ./libft/%.c, ./obj/%.o, $(LIBFT)) 	$(patsubst ./src/%.c, ./obj/%.o, $(SRC)) \
			$(patsubst ./parsing/%.c, ./obj/%.o, $(PARSER)) $(patsubst ./execution/%.c, ./obj/%.o, $(EXEC))\
			$(patsubst ./builtin/%.c, ./obj/%.o, $(BUILT))
NAME = minishell

CC = cc

CFLAGS = -ggdb3 -Wall -Wextra -Wunreachable-code  \
		 -I$(HOME)/.brew/opt/readline/include

INC = include

READLINE = -L$(HOME)/.brew/opt/readline/lib

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) $(READLINE) -lreadline -lhistory -I$(INC) -o $(NAME)

./obj/%.o : ./libft/%.c $(INCL)
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

./obj/%.o : ./src/%.c $(INCL)
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

./obj/%.o : ./parsing/%.c $(INCL)
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

./obj/%.o : ./execution/%.c $(INCL)
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

./obj/%.o : ./builtin/%.c $(INCL)
	$(CC) -c $(CFLAGS) -I$(INC) $< -o $@

run :
	@./$(NAME)
clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
re : fclean all
