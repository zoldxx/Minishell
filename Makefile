NAME = minishell

# SRC 
SRC = main.c init.c free_utils.c exec.c lst_block.c parsing3.c single_command.c multiple_command.c \
				check_error.c check_error_2.c check_error_3.c is_builtin_echo.c exit_et_env.c \
				env.c lst_env.c export.c export_utils.c hide_env.c lst_redir.c expand_copy.c \
				expand_redir.c expand_redir_norm.c expand_command.c split_expand.c \
				cd.c utils.c unset.c free_utils_2.c free_utils_3.c pwd.c \
				hide_env_utils.c parsing_2.c parsing_3.c parsing_4.c heredoc.c lst_garbage.c lst_garbage2.c free_utils_grb.c \
				expand_2.c expand_3.c expand_4.c expand_utils.c single_command_2.c single_command_3.c \
				multiple_command_2.c multiple_command_3.c multiple_command_4.c split_expand_utils.c split_expand_2.c split_expand_3.c \
				expand_5.c expand_6.c expand_7.c expand_8.c expand_9.c utils2.c ft_minisplit.c ft_minisubstr.c signals.c
				
SRC_PATH = src/

MY_SOURCES := $(addprefix $(SRC_PATH),$(SRC))

OBJ := $(MY_SOURCES:.c=.o)

MY_OBJECTS := $(addprefix build/, $(OBJ))

DEPS := $(MY_OBJECTS:.o=.d)

LIBFT_PATH = libft/

LIBFT_FILE = libft.a

LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

FTPRINTF_PATH = libft/ft_printf/

FTPRINTF_FILE = libftprintf.a

FTPRINTF_LIB = $(addprefix $(FTPRINTF_PATH), $(FTPRINTF_FILE))

GNL_PATH = libft/get_next_line/

GNL_FILE = get_next_line.a

GNL_LIB	= $(addprefix $(GNL_PATH), $(GNL_FILE))

CFLAGS = -Wall -Wextra -Werror -MMD

RM = rm -rf

CC = cc

$(NAME): $(addprefix $(LIBFT_PATH), $(LIBFT_FILE)) $(MY_OBJECTS)
		@$(CC) $(CFLAGS) -lreadline $(MY_OBJECTS) $(LIBFT_LIB) $(FTPRINTF_LIB) $(GNL_LIB) -o $(NAME)

all: $(NAME)

$(addprefix $(LIBFT_PATH), $(LIBFT_FILE)):
		@make -sC $(LIBFT_PATH)

libft: $(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

clean:
		@make clean -sC $(LIBFT_PATH)
		rm -rf build/src
		rm -rf build
		@$(RM) $(MY_OBJECTS)
		@$(RM) $(DEPS)

fclean: clean
		@$(RM) $(LIBFT_LIB)
		@$(RM) $(FTPRINTF_LIB)
		@$(RM) $(GNL_LIB)
		@$(RM) $(NAME)

re: fclean $(NAME)

build:
	mkdir build
	mkdir build/src

build/%.o: %.c | build
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all clean fclean re libft

-include $(DEPS)
