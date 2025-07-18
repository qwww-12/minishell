CC = cc

# CFLAGS = -Wall -Wextra -Werror

RFLG = -lreadline

NAME = minishell

LIB = ./libft/libft.a

SRC = 	minishell.c									\
		./parsing/asm_cmd.c							\
		./parsing/input/input.c						\
		./parsing/tokens_core/list_tokens.c			\
		./parsing/tokens_core/refactor_tokens.c		\
		./parsing/tokens_core/unquotes.c			\
		./parsing/tokens_core/utils0_tokens.c		\
		./parsing/tokens_core/utils1_tokens.c		\
		./parsing/tokens_core/utils3_tokens.c		\
		./parsing/envp/env_expander.c				\
		./parsing/envp/env_heredoc.c				\
		./parsing/envp/env_list.c					\
		./parsing/envp/env_default.c				\
		./parsing/envp/env_split.c					\
		./parsing/envp/exp_special.c				\
		./parsing/envp/utils_env.c					\
		./parsing/envp/utils1_env.c					\
		./parsing/envp/utils2_env.c					\
		./parsing/envp/env_leaks.c					\
		./parsing/cmd/list_cmd.c					\
		./parsing/cmd/utils_cmd.c					\
		./parsing/cmd/nodes_cmd.c					\
		./parsing/cmd/content_cmd.c					\
		./parsing/syntax/scrap.c					\
		./parsing/syntax/utils_scrap.c				\
		./double/exit_status.c						\
		./double/signal.c							\
		./double/error.c							\
		./double/v_free.c							\
		./double/s_free.c							\
		./execution/core_exec.c						\
		./execution/heredooc.c						\
		./execution/leaks_fd.c						\
		./execution/redirections.c					\
		./execution/pipe.c							\
		./execution/t_envutils.c					\
		./execution/path.c							\
		./execution/runtime.c						\
		./execution/child.c							\
		./execution/v_error.c						\
		./execution/fd.c							\
		./execution/builtin/builtin.c				\
		./execution/builtin/ft_echo.c				\
		./execution/builtin/ft_env.c				\
		./execution/builtin/ft_export.c				\
		./execution/builtin/ft_unset.c				\
		./execution/builtin/ft_exit.c				\
		./execution/builtin/ft_cd.c					\
		./execution/builtin/utils/export_utils_0.c	\
		./execution/builtin/utils/exit_utils_0.c	\
		./execution/builtin/utils/cd_utils_0.c		\

HDR = 		minishell.h 					\
		 	./parsing/include/token.h		\
		 	./parsing/include/syntax.h		\

OBJ = $(SRC:.c=.o)

SRC_LIB = 	./libft/ft_strjoin.c 	\
			./libft/ft_strdup.c 	\
			./libft/ft_strlen.c 	\
			./libft/ft_memcpy.c		\
			./libft/ft_substr.c		\
			./libft/ft_strncpy.c	\
			./libft/ft_isalpha.c	\
			./libft/ft_isdigit.c	\
			./libft/ft_isalnum.c	\
			./libft/ft_strcmp.c		\
			./libft/ft_itoa.c		\
			./libft/ft_split.c		\
			./libft/ft_atoi.c		\

OBJ_LIB = $(SRC:.c=.o)

HDR_LIB = ./libft/libft.h

S_GNL = ./execution/get_next_line/gnl.c			\
		./execution/get_next_line/gnl_utils.c	\

HDR_GNL = ./parsing/get_next_line/gnl.h

OBJ_GNL = $(S_GNL:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_GNL) $(LIB)
	$(CC) $(CFLAGS) $(OBJ_GNL) $(OBJ) $(LIB) -I$(HOME)/.brew/opt/readline/include -L$(HOME)/.brew/opt/readline/lib -lreadline -o $@ $(RFLG)

./parsing/get_next_line/%.o: ./parsing/get_next_line/%.c $HDR_GNL
	$(CC) $(CFALGS) -c $< -o $@

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(SRC_LIB) $(HDR_LIB)
	$(MAKE) -C ./libft

clean:
	rm -f $(OBJ_GNL)
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all