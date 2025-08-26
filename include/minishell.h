/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:54 by hguo              #+#    #+#             */
/*   Updated: 2025/08/26 20:46:06 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "libft.h"
# include "parse.h"
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char		*line;
	t_token		*tokens;
	t_token		*current;
	t_node		*tree;
	t_parse_err	parse_err;
	t_env		*envlst;
	int			exit_s;
}	t_minishell;

#endif
