/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:01:16 by hguo              #+#    #+#             */
/*   Updated: 2025/08/12 18:37:09 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define PROMPT "minishell👾 "

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
	struct s_token	*next;
	struct s_token	*before;
}	t_token;

// token_add_to_end.c
int		add_sep_to_end(t_token_type type, char **line, t_token **token_list);
int		add_word_to_end(char **line, t_token **token_list);

// token_handler.c
int		handler_sep(char **line, t_token **token_list);
t_token *token_handler(char *line);

// token_list.c
t_token	*create_new_token(char *value, t_token_type type);
void	token_list_add_back(t_token **list, t_token *new_token);
void	clear_token_list(t_token **list);

// token_util.c
void	skip_space(char **line);

// token.c
t_token	*tokenizer(void);

#endif
