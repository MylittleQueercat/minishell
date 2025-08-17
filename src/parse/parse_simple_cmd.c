/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:24:03 by hguo              #+#    #+#             */
/*   Updated: 2025/08/17 14:09:20 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

int	parse_to_list(t_io_node **io_list)
{
	t_token_type	io_type;
	t_io_node		*tmp_io_node;

	if (g_minishell.parse_err.type)
		return (0);
	while (g_minishell.current && is_redir(g_minishell.current->type))
	{
		io_type = g_minishell.current->type;
		move_to_next_token();
		if (!g_minishell.current)
			return (set_parse_arr(E_SYNTAX), 0);
		if (!g_minishell.cureent->type != T_WORD)
			return (set_parse_err(E_SYNTAX), 0);
		tmp_io_node = create_new_io_node(io_type, g_minishell.current->value);
		add_io_node_to_end(io_list, tmp_io_node);
		move_to_next_token();
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

int	parse_args(char **args)
{
	char	*tmp;

	if (g_minishell.parse_err.type)
		return (0);
	if (!*args)
	{
		*args = ft_strdup("");
		return (0);
	}
	while (g_minishell.current &&g_minishell.current->type == T_WORD)
	{
		tmp = *args;
		*args = ft_strjoin_with(*args, g_minishell.current->value, ' ');
		if (!*args)
			return (free(tmp), 0);
		free(tmp);
		move_to_next_token();
	}
	return (1);
} 

t_node	*parse_simple_cmd(void)
{
	t_node *node;

	if (g_minishell.parse_err.type)
		return (NULL);
	node = create_new_node(N_CMD);
	if (!node)
		return (set_parse_err(E_MEMORY), NULL);
	while (g_minishell.current && (g_minishell.current->type == T_WORD
			|| is_redir(g_minishell.current->type)))
	{
		if (g_minishell.current->type == T_WORD)
		{
			if (!parse_args(&(node->args)))
				return (clear_cmd_node(node), set_parse_err(E_MEMORY), NULL);
		}
		else if (is_redir(g_minishell.current->type))
		{
			if (!parse_to_list(&(node->io_list)))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}
