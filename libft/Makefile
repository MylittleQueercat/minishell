# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aprigent <marvin42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 17:05:35 by aprigent          #+#    #+#              #
#    Updated: 2025/05/03 11:07:05 by aprigent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS_DIR = ./srcs/

OBJS_DIR = ./.objs/

SRCS = ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_memcpy.c ft_strchr.c \
	   ft_strnstr.c ft_toupper.c ft_isprint.c ft_strlen.c ft_strrchr.c ft_strtrim.c \
	   ft_isascii.c ft_bzero.c ft_memchr.c ft_memset.c ft_strncmp.c ft_tolower.c \
	   ft_memmove.c ft_memcmp.c ft_putstr_fd.c ft_strlcat.c ft_split.c \
	   ft_substr.c ft_calloc.c ft_itoa.c ft_putchar_fd.c ft_strdup.c ft_strmapi.c \
	   ft_putendl_fd.c ft_striteri.c ft_putnbr_fd.c ft_strjoin.c ft_strlcpy.c ft_realloc.c \

BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
		ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstmap_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c

PRINTF = ft_printf.c parse_flags.c params_handler.c print_char.c print_str.c \
	   print_pointer.c print_int.c print_unsigned.c print_hex.c utils.c \
	   parse_utils.c ft_itoa_unsigned.c \

GNL = get_next_line.c get_next_line_utils.c

ARENA = arena.c arena_calloc.c arena_split.c

OBJS = $(SRCS:%.c=${OBJS_DIR}%.o) $(BONUS:%.c=${OBJS_DIR}%.o) \
	$(PRINTF:%.c=${OBJS_DIR}%.o) $(GNL:%.c=${OBJS_DIR}%.o) \
	$(ARENA:%.c=${OBJS_DIR}%.o)

DEPS = $(OBJS:.o=.d)

CC = cc

CFLAGS = -Wall -Werror -Wextra -I./includes -MMD -MP

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(OBJS:.o=.d)
