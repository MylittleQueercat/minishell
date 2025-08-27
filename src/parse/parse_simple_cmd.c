/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:24:03 by hguo              #+#    #+#             */
/*   Updated: 2025/08/17 14:09:20 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_to_list(t_minishell *sh, t_token **it, t_io_node **io_list)
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
		tmp_io_node = create_new_io_node(io_type, (*it)->value);
		if (!tmp_io_node)
			return (set_parse_err(sh, E_MEMORY), 0);
		add_io_node_to_end(io_list, tmp_io_node);
		*it = (*it)->next;
	}
	return (1);
}

char	*ft_strjoin_with(char const *s1, char const *s2, char c)
{
	char	*result;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if (!c || !ft_strlen(s1) || !ft_strlen(s2))
		return (ft_strjoin(s1, s2));
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	result = ft_calloc(len, sizeof(char));
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

int	parse_args(t_token **it, char **raw_args)
{
	char	*old;
	char	*joined;

	if (!*raw_args)
	{
		*raw_args = ft_strdup("");
		if (!*raw_args)
			return (0);
	}
	while (*it && (*it)->type == T_WORD)
	{
		old = *raw_args;
		if (old[0] != '\0')
			joined = ft_strjoin_with(old, (*it)->value, ' ');
		else
			joined = ft_strdup((*it)->value);
		if (!joined)
			return (0);
		*raw_args = joined;
		if (old != NULL)
			free(old);
		*it = (*it)->next;
	}
	return (1);
} 

t_node	*read_simple_cmd(t_minishell *sh, t_token **it)
{
	t_node *node;

	if (sh->parse_err.type)
		return (NULL);
	node = create_new_node(N_CMD);
	if (!node)
		return (set_parse_err(sh, E_MEMORY), NULL);
	while (*it && ((*it)->type == T_WORD || is_redir((*it)->type)))
	{
		if ((*it)->type == T_WORD)
		{
			if (!parse_args(it, &(node->raw_args)))
				return (clear_cmd_node(node), set_parse_err(sh, E_MEMORY), NULL);
		}
		else
		{
			if (!parse_to_list(sh, it, &node->io_list))
				return (clear_cmd_node(node), NULL);
		}
	}
	return (node);
}