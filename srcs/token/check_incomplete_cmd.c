/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_incomplete_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:19:53 by hguo              #+#    #+#             */
/*   Updated: 2025/10/03 19:28:35 by hguo             ###   ########.fr       */
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

static int	print_sep_error(t_token *last)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (last->type == T_PIPE)
		ft_putstr_fd("|", 2);
	else if (last->type == T_AND)
		ft_putstr_fd("&&", 2);
	else if (last->type == T_OR)
		ft_putstr_fd("||", 2);
	ft_putstr_fd("'\n", 2);
	g_st = 2;
	return (0);
}

t_token	*token_handler_line(t_sh *sh, char *line)
{
	t_token	*list;
	char	*old;

	if (!line || !*line)
		return (NULL);
	old = sh->line;
	sh->line = line;
	list = token_handler(sh);
	sh->line = old;
	return (list);
}

static int	handle_incomplete(t_sh *sh, t_token **token_list)
{
	char	*more;
	t_token	*new_list;
	t_token	*last;

	more = readline(make_my_prompt(sh, 1));
	if (!more)
	{
		ft_putstr_fd(
			"minishell: syntax error: unexpected end of file\n", 2);
		g_st = 2;
		return (0);
	}
	new_list = token_handler_line(sh, more);
	free(more);
	if (!new_list)
		return (0);
	last = *token_list;
	while (last->next)
		last = last->next;
	last->next = new_list;
	return (1);
}

int	check_incomplete_cmd(t_sh *sh, t_token *token_list)
{
	t_token	*last;

	last = token_list;
	while (last && last->next)
		last = last->next;
	if (last && token_list == last
		&& (last->type == T_PIPE || last->type == T_AND || last->type == T_OR))
		return (print_sep_error(last));
	if (is_incomplete(last))
		return (handle_incomplete(sh, &token_list));
	return (1);
}
