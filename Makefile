NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR)/includes -I./includes -MMD -MP

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_DIR = ./srcs/
OBJS_DIR = ./.objs/

SRCS = $(addprefix $(SRCS_DIR), main.c, exec.c)
OBJS = $(SRCS:$(SRCS_DIR)%.c=${OBJS_DIR}%.o)

LDFLAGS = -L$(LIBFT_DIR) -lft

DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
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
