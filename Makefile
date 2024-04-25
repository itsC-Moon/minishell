# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 11:33:30 by hibenouk          #+#    #+#              #
#    Updated: 2024/04/21 12:18:49 by hibenouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIBFT 	= $(addprefix ./libft/,  alpha.c alpha2.c env_func_outils.c error.c ft_atoi.c ft_free.c \
			ft_free2.c ft_itoa.c ft_printf.c ft_put.c ft_split.c ft_strchr.c ft_strcmp.c\
			ft_strdup.c ft_strjoin.c get_args2.c jump2.c list_func.c static_func.c string_func.c)

BUILT 	= $(addprefix ./builtin/,  builtin.c cd_func.c cd_func_utils.c echo_func.c env_func.c\
			exit_func.c export_func.c export_utils.c pwd_func.c unset_func.c )

PARSER 	= $(addprefix ./parsing/, expand.c expand2.c get_args.c here_doc.c jump.c parsing.c tokenizer.c \
			tools.c tools2.c)

EXEC 	= $(addprefix ./execution/, cmd_check.c env_2d2lst.c env_search.c execute.c \
			files_handle.c here_doc_exec.c path_handle.c pipe.c \
			pipe_utils.c)

SRC 	= $(addprefix ./src/, main.c signal.c event_loop.c)

INCL 	= $(addprefix ./include/, libft.h minishell.h)

OBJ 	= $(LIBFT:.c=.o) $(SRC:.c=.o) $(PARSER:.c=.o) $(EXEC:.c=.o) $(BUILT:.c=.o)
			
			
NAME = minishell

CC = cc

INC = include

CFLAGS = -Wall -Wextra -Werror -I$(HOME)/.brew/opt/readline/include -I$(INC)

READLINE = -L$(HOME)/.brew/opt/readline/lib

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) $(READLINE) -lreadline -lhistory -I$(INC) -o $(NAME)

%.o : %.c $(INCL)
	$(CC) -c -I$(INC) $(CFLAGS) $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
re : fclean all
