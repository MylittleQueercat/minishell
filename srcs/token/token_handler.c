/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:07 by hguo              #+#    #+#             */
/*   Updated: 2025/10/03 18:55:03 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  In this file, we'll split the entire command string entered by the user
into a token linked list:

  1. Iterate through the input string.
  2. Split the tokens according to the rules.
  3. Save to the linked list.
*/

int	handler_sep(t_sh *sh, char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (add_sep_to_end(sh, T_RD_HEREDOC, line, token_list) && 1);
	else if (!ft_strncmp(*line, ">>", 2))
		return (add_sep_to_end(sh, T_RD_ADD_END, line, token_list) && 1);
	else if (!ft_strncmp(*line, "<", 1))
		return (add_sep_to_end(sh, T_RD_IN, line, token_list) && 1);
	else if (!ft_strncmp(*line, ">", 1))
		return (add_sep_to_end(sh, T_RD_OUT, line, token_list) && 1);
	else if (!ft_strncmp(*line, "(", 1))
		return (add_sep_to_end(sh, T_PAREN_OP, line, token_list) && 1);
	else if (!ft_strncmp(*line, ")", 1))
		return (add_sep_to_end(sh, T_PAREN_CL, line, token_list) && 1);
	else if (!ft_strncmp(*line, "&&", 2))
		return (add_sep_to_end(sh, T_AND, line, token_list) && 1);
	else if (!ft_strncmp(*line, "||", 2))
		return (add_sep_to_end(sh, T_OR, line, token_list) && 1);
	else if (!ft_strncmp(*line, "&", 1))
	{
		ft_putstr_fd("minishell: '&' not supported (no background jobs)\n", 2);
		g_st = 2;
		(*line)++;
		return (-1);
	}
	else
		return (add_sep_to_end(sh, T_PIPE, line, token_list) && 1);
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
	g_st = 2;
	return (0);
}

int	check_incomplete_cmd(t_sh *sh, t_token *token_list)
{
	t_token	*last;
	char	*more;
	t_token	*new_list;

	last = token_list;
	while (last && last->next)
		last = last->next;
	if (last && !last->next &&
		(last->type == T_PIPE || last->type == T_AND || last->type == T_OR))
		return (print_sep_error(sh, last));
	if (is_incomplete(last))
	{
		more = readline(make_my_prompt(sh, 1));
		if (!more)
		{
			ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
			g_st = 2;
			return (0);
		}
		sh->line = ft_strjoin_with(sh, sh->line, " ", 0);
		sh->line = ft_strjoin_with(sh, sh->line, more, 0);
		free(more);
		new_list = token_handler(sh);
		if (!new_list)
			return (0);
		*token_list = *new_list;
	}
	return (1);
}

static int	process_token(t_sh *sh, char **p, t_token **token_list)
{
	int	ret;

	if (ft_isspace(**p))
	{
		skip_space(p);
		return (0);
	}
	if (!ft_strncmp(*p, "&&", 2) || !ft_strncmp(*p, ">", 1)
		|| !ft_strncmp(*p, "|", 1) || !ft_strncmp(*p, "<", 1)
		|| !ft_strncmp(*p, "(", 1) || !ft_strncmp(*p, ")", 1)
		|| !ft_strncmp(*p, "&", 1))
	{
		ret = handler_sep(sh, p, token_list);
		if (ret == -1)
			return (-1);
		return (!ret);
	}
	return (!add_word_to_end(sh, p, token_list));
}

t_token	*token_handler(t_sh *sh)
{
	int		state;
	t_token	*token_list;
	char	*p;

	token_list = NULL;
	p = sh->line;
	while (*p)
	{
		state = process_token(sh, &p, &token_list);
		if (state != 0)
			return (NULL);
	}
	if (!check_incomplete_cmd(sh, token_list))
		return (NULL);
	return (token_list);
}
