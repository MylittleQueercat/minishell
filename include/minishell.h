/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:54 by hguo              #+#    #+#             */
/*   Updated: 2025/08/12 19:22:50 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "libft.h"
# include "parse.h"

typedef struct s_minishell
{
	char		*line;
	t_token		*tokens;
	t_token		*current;
	t_node		*tree;
}	t_minishell;

extern t_minishell	g_minishell;

#endif
