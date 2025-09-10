NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR)/includes -I./includes -MMD -MP \
		 -g3

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_DIR = ./srcs/

OBJS_DIR = ./.objs/

BUILTIN_DIR = ./srcs/builtins/
PARSE_DIR = ./srcs/parse/
EXPAND_DIR = ./srcs/expander/
TOKEN_DIR = ./srcs/token/

SRCS = main.c exec.c path.c utils.c init_env.c loop.c error_exit.c free.c \
		clean.c mini_signal.c init_minishell.c pipe.c ft_atoll.c

PARSE_SRCS = parse.c parse_clear.c parse_err.c parse_node.c parse_simple_cmd.c \
			 parse_util.c

EXPAND_SRCS = expand.c expand_asterisker.c expand_globber.c expand_heredoc.c \
			  expand_pre_handle.c expand_split.c expand_util.c globber_util.c \
			  throw_quotes.c

TOKEN_SRCS = token.c token_add_to_end.c token_handler.c token_list.c \
			 token_util.c

BUILTIN_SRCS = echo.c env.c pwd.c cd.c export.c unset.c export_utils.c exit.c

OBJS = $(SRCS:%.c=${OBJS_DIR}%.o) \
		$(BUILTIN_SRCS:%.c=${OBJS_DIR}builtins/%.o) \
		$(PARSE_SRCS:%.c=${OBJS_DIR}parse/%.o) \
		$(EXPAND_SRCS:%.c=${OBJS_DIR}expander/%.o) \
		$(TOKEN_SRCS:%.c=${OBJS_DIR}token/%.o)

LDFLAGS = -L$(LIBFT_DIR) -lft

DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) -lreadline -lncurses

${OBJS_DIR}%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}builtins/%.o: $(BUILTIN_DIR)%.c
	@mkdir -p $(OBJS_DIR)builtins
	$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}parse/%.o: $(PARSE_DIR)%.c
	@mkdir -p $(OBJS_DIR)parse
	$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}expander/%.o: $(EXPAND_DIR)%.c
	@mkdir -p $(OBJS_DIR)expander
	$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}token/%.o: $(TOKEN_DIR)%.c
	@mkdir -p $(OBJS_DIR)token
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
