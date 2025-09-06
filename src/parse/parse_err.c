/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:06:55 by hguo              #+#    #+#             */
/*   Updated: 2025/09/04 17:49:08 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_parse_err(t_minishell *sh, t_parse_err_type type)
{
	sh->parse_err.type = type;
}

static const char	*token_type_str(t_token_type t)
{
	if (t == T_WORD)
		return ("T_IDENTIFIER");
	if (t == T_RD_IN)
		return ("<");
	if (t == T_RD_OUT)
		return (">");
	if (t == T_RD_HEREDOC)
		return ("<<");
	if (t == T_RD_ADD_END)
		return (">>");
	if (t == T_PIPE)
		return ("|");
	if (t == T_PAREN_OP)
		return ("(");
	if (t == T_PAREN_CL)
		return (")");
	if (t == T_AND)
		return ("&&");
	if (t == T_OR)
		return ("||");
	if (t == T_NEWLINE)
		return ("newline");
	return ("token");
}

void	handle_parse_err(t_minishell *sh)
{
	t_token_type	tok;

	if (!sh)
		return ;
	if (sh->parse_err.type == 0)
		return ;
	if (sh->parse_err.type == E_SYNTAX)
	{
		if (sh->current)
			tok = sh->current->type;
		else
			tok = T_NEWLINE;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd((char *)token_type_str(tok), 2);
		ft_putstr_fd("'\n", 2);
		sh->exit_s = 258;
	}
	clear_ast(&sh->tree);
	ft_bzero(&sh->parse_err, sizeof(sh->parse_err));
}
