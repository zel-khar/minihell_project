NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
SRCS_DIR = src/
INCS_DIR = inc/
OBJS_DIR = obj/
SRCS = \
	$(SRCS_DIR)main.c \
	$(SRCS_DIR)core/signals.c \
	$(SRCS_DIR)core/gc.c \
	$(SRCS_DIR)env/env.c \
	$(SRCS_DIR)env/env_utils.c \
	$(SRCS_DIR)tokenizer/tokenizer_core.c \
	$(SRCS_DIR)tokenizer/tokenizer_utils.c \
	$(SRCS_DIR)tokenizer/tokenizer_expand.c \
	$(SRCS_DIR)tokenizer/tokenizer_expand_utils.c \
	$(SRCS_DIR)tokenizer/expansion.c \
	$(SRCS_DIR)tokenizer/tokenizer_expand_utils2.c \
	$(SRCS_DIR)tokenizer/tokenizer_core_utils.c \
	$(SRCS_DIR)parser/parser.c \
	$(SRCS_DIR)parser/parser_utils.c \
	$(SRCS_DIR)parser/parser_validation.c \
	$(SRCS_DIR)parser/parser_utils2.c \
	$(SRCS_DIR)exec/execution.c \
	$(SRCS_DIR)exec/exec_utils.c \
	$(SRCS_DIR)exec/execute_single_builtin.c \
	$(SRCS_DIR)exec/execute_single_external.c \
	$(SRCS_DIR)exec/execute_single_cmd.c \
	$(SRCS_DIR)exec/pipeline_run.c \
	$(SRCS_DIR)exec/pipeline_entry.c \
	$(SRCS_DIR)exec/pipeline_utils.c \
	$(SRCS_DIR)exec/pipeline_utils2.c \
	$(SRCS_DIR)exec/process.c \
	$(SRCS_DIR)exec/pipes.c \
	$(SRCS_DIR)exec/redirection_utils.c \
	$(SRCS_DIR)exec/redirection.c \
	$(SRCS_DIR)exec/execution_path_utils.c \
	$(SRCS_DIR)exec/execution_path.c \
	$(SRCS_DIR)exec/execution_validate.c \
	$(SRCS_DIR)builtins/builtins.c \
	$(SRCS_DIR)builtins/export.c \
	$(SRCS_DIR)builtins/unset.c \
	$(SRCS_DIR)builtins/cd.c \
	$(SRCS_DIR)builtins/exit.c \
	$(SRCS_DIR)builtins/export_utils2.c \
	$(SRCS_DIR)builtins/export_utils.c \
	$(SRCS_DIR)init.c \
	$(SRCS_DIR)main_helper.c

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_SRCS = ft_isdigit.c ft_split.c ft_strjoin.c ft_itoa.c ft_putendl_fd.c ft_strndup.c ft_atoi.c ft_isalnum.c ft_strcmp.c ft_putstr_fd.c ft_putchar_fd.c ft_isalpha.c ft_strlen.c ft_strdup.c ft_memcpy.c ft_utils.c
LIBFT_OBJS = $(addprefix $(OBJS_DIR)libft/,$(LIBFT_SRCS:.c=.o))
OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o) $(LIBFT_OBJS)
INCLUDES = -I$(INCS_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)libft/%.o: $(LIBFT_DIR)%.c $(LIBFT_DIR)libft.h $(INCS_DIR)minishell.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re