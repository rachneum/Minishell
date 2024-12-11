# -----------------------------------Makefile------------------------------------
NAME	= minishell

# -----------------------------------Sources-------------------------------------

HEADER	= /includes/shell.h 

SHELL_SRCS 	= token/token_utils.c\
				token/token_utils_1.c\
				token/token_utils_2.c\
				token/token_utils_3.c\
				token/token.c\
				token/token1.c\
				token/special_split.c\
				parsing/parse.c\
				parsing/parse_utils.c\
				parsing/parse_utils_1.c\
				parsing/cmd.c\
				env/env.c\
				env/env_utils.c\
				shell.c\
				exec/exec_utils.c\
				exec/exec_utils_2.c\
				exec/pipex_utils.c\
				exec/redirect.c\
				exec/ft_split.c\
				exec/pipex.c\
				exec/handle_redirect.c\
				exec/handle_heredoc.c\
				exec/exec_built_in.c\
				built_in/built_in.c\
				built_in/my_unset.c\
				built_in/my_export.c\
				built_in/built_in_utils.c\
				built_in/my_exit.c\
				built_in/my_cd.c\
				built_in/export_utils.c\
				built_in/my_cd_utils.c\
				signal.c

SHELL_SRC	= ${SHELL_SRCS}

ALL_SRC		= ${SHELL_SRC} 

OBJS	= ${ALL_SRC:.c=.o}

# -----------------------------------Compilation------------------------------------

FT_FOLDER = ./libft

FT = ${FT_FOLDER}/libft.a

CC		= cc -g

FLAGS	= -Wall -Wextra -Werror

RDL_PAT	= $(shell brew --prefix readline)

ifeq ($(CURRENT_USER), thomvan-)
	READ_FLAGS = -L/Users/$(shell whoami)/homebrew/opt/readline/lib -I/Users/$(shell whoami)/homebrew/opt/readline/include -lreadline
else
	READ_FLAGS = -L Users/$(shell whoami)/.brew/opt/readline/lib -I Users/$(shell whoami)/.brew/opt/readline/include -lreadline
endif

RDL_LIB = -lreadline -lhistory -L $(RDL_PAT)/lib

RM		= rm -f

MAKE_FT = make -s -C ${FT_FOLDER}

# -----------------------------------Libraries--------------------------------------

INCLUDES = -I ./includes ./libft/includes

# -----------------------------------Rules------------------------------------------

all: ${NAME}

$(NAME): $(OBJS) ${FT}
	@$(CC) $(FLAGS) -o $(NAME)  $(OBJS) ${FT} ${READ_FLAGS}

${FT}: 
	@${MAKE_FT}

%.o: %.c ${HEADER}
	@${CC} ${FLAGS} -c ${INCLUDES} $< -o $@

re: fclean all

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}
	@${MAKE_FT} fclean

# -----------------------------------.phony--------------------------------------

.PHONY: all clean fclean re