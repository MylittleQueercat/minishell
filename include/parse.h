/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:41:08 by hguo              #+#    #+#             */
/*   Updated: 2025/08/12 19:08:00 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD,
}	t_node_type;
// Everything that 'is not a pipe or a logical operator’ will be N_CMD.

typedef	enum e_io_type
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
	int					heredoc;
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
}	t_node;

#endif
