/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:41:08 by hguo              #+#    #+#             */
/*   Updated: 2025/09/29 14:49:15 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_sh	t_sh;
typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;
typedef struct s_cmd		t_cmd;

typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD,
	N_AMP,
}	t_node_type;
// Everything that 'is not a pipe or a logical operator’ will be N_CMD.

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_ADD_END,
}	t_io_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*raw_value;
	char				**exec_value;
	int					quoted;
	struct s_io_node	*before;
	struct s_io_node	*next;
}	t_io_node;

typedef struct s_node
{
	t_node_type		type;
	t_io_node		*io_list;
	char			*raw_args;
	char			**exec_args;
	struct s_node	*left;
	struct s_node	*right;
	t_cmd			*cmd;
	int				is_in_pipe;
}	t_node;

typedef enum e_parse_err_type
{
	E_MEMORY = 1,
	E_SYNTAX,
}	t_parse_err_type;
// We set memory error as 1, for 0 represent 'no error'.

typedef struct s_parse_err
{
	t_parse_err_type	type;
	char				*msg;
}	t_parse_err;

// parse_node.c
t_node_type	get_node_type(t_token_type type);
t_node		*create_new_node(t_sh *sh, t_node_type type);
t_io_type	get_io_type(t_token_type type);
t_io_node	*create_new_io_node(t_sh *sh, t_token_type type, char *value);
void		add_io_node_to_end(t_io_node **list, t_io_node *new);

// parse_err.c
void		set_parse_err(t_sh *sh, t_parse_err_type type);
void		handle_parse_err(t_sh *sh);

// parse_util.c
int			is_bi_operator(t_token *tok);
int			get_priority(t_token_type type);
int			curr_priority(t_token *tok);
int			is_redir(t_token_type type);

// parse_simple_cmd.c
int			parse_to_list(t_sh *sh, t_token **it, t_io_node **io_list);
char		*ft_strjoin_with(t_sh *sh, char const *s1, char const *s2, char c);
int			parse_args(t_sh *sh, t_token **it, char **raw_args);
t_node		*read_simple_cmd(t_sh *sh, t_token **it);

// parse.c
t_node		*parse_cmd_unit(t_sh *sh, t_token **it);
t_node		*comb_cmd(t_sh *sh, t_token_type op, t_node *lf, t_node *rg);
t_node		*parse_cmd(t_sh *sh, t_token **it, int min_prio);
t_node		*parse(t_sh *sh);

#endif
