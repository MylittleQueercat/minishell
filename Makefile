NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR)/includes -I./includes -MMD -MP


LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_DIR = ./srcs/
OBJS_DIR = ./.objs/
BUILTIN_DIR = ./srcs/builtins/

SRCS = main.c exec.c path.c utils.c init_env.c loop.c split.c ft_atoll.c
BUILTIN_SRCS = echo.c env.c pwd.c cd.c export.c unset.c export_utils.c exit.c
OBJS = $(SRCS:%.c=${OBJS_DIR}%.o) $(BUILTIN_SRCS:%.c=${OBJS_DIR}%.o)

LDFLAGS = -L$(LIBFT_DIR) -lft

DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) -lreadline -lncurses

${OBJS_DIR}%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}%.o: $(BUILTIN_DIR)%.c
	@mkdir -p $(OBJS_DIR)
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
