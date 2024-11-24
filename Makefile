# -----------------------------------Makefile------------------------------------
NAME	= minishell

# -----------------------------------Sources-------------------------------------

HEADER	= /includes/shell.h 

SHELL_SRCS 	= token/token_utils.c\
				token/token_utils_1.c\
				token/token_utils_2.c\
				token/token_utils_3.c\
				token/token.c\
				token/special_split.c\
				parsing/parse.c\
				parsing/parse_utils.c\
				parsing/parse_utils_1.c\
				env.c\
				shell.c\
				utils/extra.c\
				exec/exec_utils.c\
				exec/ft_split.c\
				exec/pipex.c\
				exec/handle_redirect.c\
				exec/handle_heredoc.c\
				exec/exec_built_in.c\
				built_in/built_in.c\
				built_in/built_in_1.c

SHELL_SRC	= ${SHELL_SRCS}

ALL_SRC		= ${SHELL_SRC} 

OBJS	= ${ALL_SRC:.c=.o}

# -----------------------------------Compilation------------------------------------

FT_FOLDER = ./libft

FT = ${FT_FOLDER}/libft.a

CC		= cc -g #-fsanitize=address

FLAGS	= -Wall -Wextra -Werror

READ_FLAGS = -L/Users/rachou/.brew/opt/readline/lib -I/Users/rachou/.brew/opt/readline/include -lreadline

LIB		= ar -rc

RM		= rm -f

MAKE_FT = make -s -C ${FT_FOLDER}

# -----------------------------------Libraries--------------------------------------

INCLUDES = -I ./includes ./libft/includes

# -----------------------------------Rules------------------------------------------

all: ${NAME}

$(NAME): $(OBJS) ${FT}
	$(CC) $(FLAGS) -o $(NAME)  $(OBJS) ${FT} ${READ_FLAGS}

${FT}: 
		${MAKE_FT}

%.o: %.c ${HEADER}
	${CC} ${FLAGS} -c ${INCLUDES} $< -o $@

re: fclean all

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}
		${MAKE_FT} fclean

# -----------------------------------.phony--------------------------------------

.PHONY: all clean fclean re