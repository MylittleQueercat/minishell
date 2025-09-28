/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:01:16 by hguo              #+#    #+#             */
/*   Updated: 2025/09/28 18:25:08 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"
# include <stddef.h>

# define PROMPT "minishell👾 "

typedef struct s_sh	t_sh;

typedef enum e_token_type
{
	T_WORD,
	T_RD_IN,
	T_RD_OUT,
	T_RD_HEREDOC,
	T_RD_ADD_END,
	T_PIPE,
	T_PAREN_OP,
	T_PAREN_CL,
	T_AND,
	T_OR,
	T_NEWLINE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
	struct s_token	*before;
}	t_token;

// token_add_to_end.c
int		add_sep_to_end(t_sh *m, t_token_type type, char **line, t_token **t_l);
int		is_quote(char c);
int		add_word_to_end(t_sh *sh, char **line, t_token **token_list);

// token_handler.c
int		handler_sep(t_sh *sh, char **line, t_token **token_list);
t_token	*token_handler(t_sh *sh);

// token_list.c
t_token	*create_new_token(t_sh *sh, char *value, t_token_type type);
void	token_list_add_back(t_token **list, t_token *new_token);
void	clear_token_list(t_token **list);

// token_util.c
int		is_sep(char *str);
int		ft_isspace(char c);
void	skip_space(char **str);
int		skip_quote(char *line, size_t *i);
void	print_quote_err(t_sh *sh, char c);

// token.c
t_token	*tokenizer(t_sh *sh);

#endif
