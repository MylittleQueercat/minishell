/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_incomplete_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:19:53 by hguo              #+#    #+#             */
/*   Updated: 2025/10/03 18:19:55 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_incomplete(t_token *last)
{
	if (!last)
		return (0);
	return (last->type == T_PIPE
		|| last->type == T_AND
		|| last->type == T_OR);
}

static int	print_sep_error(t_sh *sh, t_token *last)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (last->type == T_PIPE)
		ft_putstr_fd("|", 2);
	else if (last->type == T_AND)
		ft_putstr_fd("&&", 2);
	else if (last->type == T_OR)
		ft_putstr_fd("||", 2);
	ft_putstr_fd("'\n", 2);
	sh->exit_s = 2;
	return (0);
}

static int	handle_incomplete(t_sh *sh, t_token **token_list)
{
	char	*more;
	t_token	*new_list;

	more = readline(make_my_prompt(sh, 1));
	if (!more)
	{
		ft_putstr_fd(
			"minishell: syntax error: unexpected end of file\n", 2);
		sh->exit_s = 258;
		return (0);
	}
	sh->line = ft_strjoin_with(sh, sh->line, " ", 0);
	sh->line = ft_strjoin_with(sh, sh->line, more, 0);
	free(more);
	new_list = token_handler(sh);
	if (!new_list)
		return (0);
	*token_list = new_list;
	return (1);
}

int	check_incomplete_cmd(t_sh *sh, t_token *token_list)
{
	t_token	*last;

	last = token_list;
	while (last && last->next)
		last = last->next;
	if (last && !last->next
		&& (last->type == T_PIPE || last->type == T_AND || last->type == T_OR))
		return (print_sep_error(sh, last));
	if (is_incomplete(last))
		return (handle_incomplete(sh, &token_list));
	return (1);
}
