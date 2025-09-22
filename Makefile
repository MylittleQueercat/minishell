NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR)/includes -I./includes -MMD -MP \
		 -g3 -ggdb

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_DIR = ./srcs/

OBJS_DIR = ./.objs/

BUILTIN_DIR = ./srcs/builtins/
PARSE_DIR = ./srcs/parse/
EXPAND_DIR = ./srcs/expander/
TOKEN_DIR = ./srcs/token/
ARENA_DIR = ./srcs/arena/

SRCS = main.c exec.c path.c utils.c init_env.c loop.c free.c \
		clean.c mini_signal.c init_minishell.c pipe.c ft_atoll.c utils2.c \
		heredoc.c init_cmd.c

PARSE_SRCS = parse.c parse_clear.c parse_err.c parse_node.c parse_simple_cmd.c \
			 parse_util.c

EXPAND_SRCS = expand.c expand_asterisker.c expand_globber.c expand_heredoc.c \
			  expand_pre_handle.c expand_split.c expand_util.c globber_util.c \
			  throw_quotes.c

TOKEN_SRCS = token.c token_add_to_end.c token_handler.c token_list.c \
			 token_util.c

BUILTIN_SRCS = echo.c env.c pwd.c cd.c export.c unset.c export_utils.c exit.c

ARENA_SRCS = arena.c arena_calloc.c arena_split.c a_itoa.c a_strdup.c \
			  a_substr.c a_strjoin.c setup_arena.c

OBJS = $(SRCS:%.c=${OBJS_DIR}%.o) \
		$(BUILTIN_SRCS:%.c=${OBJS_DIR}builtins/%.o) \
		$(PARSE_SRCS:%.c=${OBJS_DIR}parse/%.o) \
		$(EXPAND_SRCS:%.c=${OBJS_DIR}expander/%.o) \
		$(TOKEN_SRCS:%.c=${OBJS_DIR}token/%.o) \
		$(ARENA_SRCS:%.c=${OBJS_DIR}arena/%.o)

LDFLAGS = -L$(LIBFT_DIR) -lft

DEPS = $(OBJS:.o=.d)

#  Colors & Emojis
RESET := \033[0m
BOLD  := \033[1m
DIM   := \033[2m

BLK := \033[30m
RED := \033[31m
GRN := \033[32m
YEL := \033[33m
BLU := \033[34m
MAG := \033[35m
CYN := \033[36m
WHT := \033[37m

OK      := $(GRN)✔$(RESET)
FAIL    := $(RED)✘$(RESET)
GEAR    := 🛠️
BROOM   := 🧹
BOMB    := 💣
RECYCLE := ♻️
SHELL_E := 🐚

define SHOW_BANNER
	@printf "\033[34m                                                                                                    \033[0m\n"
	@printf "\033[36m                                                                                                    \033[0m\n"
	@printf "\033[1;34m   __    __      _____      __      _    _____    _____   __    __    _____   _____       _____      \033[0m\n"
	@printf "\033[1;36m   \\ \\  / /     (_   _)    /  \\    / )  (_   _)  / ____\\ (  \\  /  )  / ___/  (_   _)     (_   _)     \033[0m\n"
	@printf "\033[1;35m   () \\/ ()       | |     / /\\ \\  / /     | |   ( (___    \\ (__) /  ( (__      | |         | |       \033[0m\n"
	@printf "\033[1;32m   / _  _ \\       | |     ) ) ) ) ) )     | |    \\___ \\    ) __ (    ) __)     | |         | |       \033[0m\n"
	@printf "\033[1;33m  / / \\/ \\ \\      | |    ( ( ( ( ( (      | |        ) )  ( (  ) )  ( (        | |   __    | |   __  \033[0m\n"
	@printf "\033[1;31m /_/      \\_\\    _| |__  / /  \\ \\/ /     _| |__  ___/ /    ) )( (    \\ \\___  __| |___) ) __| |___) ) \033[0m\n"
	@printf "\033[35m(/          \\)  /_____( (_/    \\__/     /_____( /____/    /_/  \\_\\    \\____\\ \\________/  \\________/  \033[0m\n"
	@printf "\033[34m                                                                                                    \033[0m\n"
	@printf "\033[36m                                                                                                    \033[0m\n"
	@printf "\033[1m			               Huilin and Argan                                                           \033[1m\n"
	@printf "\033[34m                                                                                                    \033[0m\n"
endef

define CLEAR_SCREEN
	@printf "\033[2J\033[H"
endef

Q := @

COLS := $(shell tput cols 2>/dev/null || echo 60)
define HR
	$(Q)printf "$(DIM)%0.s─$(RESET)" `seq 1 $(COLS)`; printf "\n"
endef

all: $(NAME)

$(NAME): $(OBJS)
	$(Q)make -C $(LIBFT_DIR)
	$(Q)$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) -lreadline -lncurses \
	 || { printf "$(FAIL) link failed\n"; exit 1; }
	$(Q)printf "$(OK) $(BOLD)$@ built successfully$(RESET)\n"
	$(CLEAR_SCREEN)
	$(SHOW_BANNER)

${OBJS_DIR}%.o: $(SRCS_DIR)%.c
	$(Q)mkdir -p $(OBJS_DIR)
	$(Q)printf "$(CYN)CC$(RESET)   %-40s → $(DIM)%s$(RESET)\n" "$<" "$@"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}builtins/%.o: $(BUILTIN_DIR)%.c
	$(Q)mkdir -p $(OBJS_DIR)builtins
	$(Q)printf "$(CYN)CC$(RESET)   %-40s → $(DIM)%s$(RESET)\n" "$<" "$@"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}parse/%.o: $(PARSE_DIR)%.c
	$(Q)mkdir -p $(OBJS_DIR)parse
	$(Q)printf "$(CYN)CC$(RESET)   %-40s → $(DIM)%s$(RESET)\n" "$<" "$@"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}expander/%.o: $(EXPAND_DIR)%.c
	$(Q)mkdir -p $(OBJS_DIR)expander
	$(Q)printf "$(CYN)CC$(RESET)   %-40s → $(DIM)%s$(RESET)\n" "$<" "$@"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}token/%.o: $(TOKEN_DIR)%.c
	$(Q)mkdir -p $(OBJS_DIR)token
	$(Q)printf "$(CYN)CC$(RESET)   %-40s → $(DIM)%s$(RESET)\n" "$<" "$@"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

${OBJS_DIR}arena/%.o: $(SRCS_DIR)arena/%.c
	$(Q)mkdir -p $(OBJS_DIR)arena
	$(Q)printf "$(CYN)CC$(RESET)   %-40s → $(DIM)%s$(RESET)\n" "$<" "$@"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(call HR)
	$(Q)printf "$(BROOM)  $(BOLD)clean$(RESET)\n"
	$(Q)make -C $(LIBFT_DIR) clean
	$(Q)rm -rf $(OBJS_DIR)
	$(Q)printf "$(OK) objects removed$(RESET)\n"

fclean: clean
	$(Q)printf "$(BOMB)  $(BOLD)fclean$(RESET)\n"
	$(Q)make -C $(LIBFT_DIR) fclean
	$(Q)rm -f $(NAME)
	$(Q)printf "$(OK) binary removed$(RESET)\n"
	$(call HR)

re:
	$(Q)$(MAKE) fclean
	$(Q)$(MAKE) all

help:
	$(call HR)
	$(Q)printf "$(BOLD)Targets$(RESET)\n"
	$(Q)printf "  make / all     — build $(NAME)\n"
	$(Q)printf "  clean          — remove objects (*.o)\n"
	$(Q)printf "  fclean         — remove objects and binary\n"
	$(Q)printf "  re             — rebuild from scratch\n"
	$(call HR)

.PHONY: all clean fclean re help

-include $(DEPS)
