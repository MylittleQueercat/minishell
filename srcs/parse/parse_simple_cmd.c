/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:24:03 by hguo              #+#    #+#             */
/*   Updated: 2025/09/28 18:32:21 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_to_list(t_sh *sh, t_token **it, t_io_node **io_list)
{
	t_token_type	io_type;
	t_io_node		*tmp_io_node;

	if (sh->parse_err.type)
		return (0);
	while (*it && is_redir((*it)->type))
	{
		io_type = (*it)->type;
		*it = (*it)->next;
		if (!*it)
			return (set_parse_err(sh, E_SYNTAX), 0);
		if ((*it)->type != T_WORD)
			return (set_parse_err(sh, E_SYNTAX), 0);
		tmp_io_node = create_new_io_node(sh, io_type, (*it)->value);
		if (!tmp_io_node)
			return (set_parse_err(sh, E_MEMORY), 0);
		tmp_io_node->quoted = (*it)->quoted;
		if (tmp_io_node->type == IO_HEREDOC)
			sh->heredoc_count++;
		add_io_node_to_end(io_list, tmp_io_node);
		*it = (*it)->next;
	}
	return (1);
}

char	*ft_strjoin_with(t_sh *m, char const *s1, char const *s2, char c)
{
	char	*result;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if (!c || !ft_strlen(s1) || !ft_strlen(s2))
		return (a_strjoin(m->a, s1, s2));
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	result = a_calloc(m->a, 1, len);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = c;
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = 0;
	return (result);
}

int	parse_args(t_sh *sh, t_token **it, char **raw_args)
{
	char	*old;
	char	*joined;

	if (!*raw_args)
	{
		*raw_args = a_strdup(sh->a, "");
		if (!*raw_args)
			return (0);
	}
	while (*it && (*it)->type == T_WORD)
	{
		old = *raw_args;
		if (old[0] != '\0')
			joined = ft_strjoin_with(sh, old, (*it)->value, ' ');
		else
			joined = a_strdup(sh->a, (*it)->value);
		if (!joined)
			return (0);
		*raw_args = joined;
		*it = (*it)->next;
	}
	return (1);
}

t_node	*read_simple_cmd(t_sh *sh, t_token **it)
{
	t_node	*node;

	if (sh->parse_err.type)
		return (NULL);
	node = create_new_node(sh, N_CMD);
	if (!node)
		return (set_parse_err(sh, E_MEMORY), NULL);
	while (*it && ((*it)->type == T_WORD || is_redir((*it)->type)))
	{
		if ((*it)->type == T_WORD)
		{
			if (!parse_args(sh, it, &node->raw_args))
				return (set_parse_err(sh, E_MEMORY), NULL);
		}
		else
		{
			if (!parse_to_list(sh, it, &node->io_list))
				return (NULL);
		}
	}
	return (node);
}
