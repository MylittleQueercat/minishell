/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:47:07 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/29 14:59:02 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "env", 3) == 0 ||
		ft_strncmp(cmd, "pwd", 3) == 0 || ft_strncmp(cmd, "exit", 4) == 0 ||
		ft_strncmp(cmd, "cd", 2) == 0 || ft_strncmp(cmd, "export", 6) == 0 ||
		ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	return (0);
}

void	build_prompt(t_sh *sh)
{
	char	*new_prompt;

	if (!sh->env->pwd)
		sh->env->pwd = a_strdup(sh->a, "~");
	new_prompt = a_strjoin(sh->a, "\033[1;32mminishell:\033[0m ", sh->env->pwd);
	if (!new_prompt)
		return ;
	sh->prompt = make_my_prompt(sh, 0);
//	sh->prompt = a_strjoin(sh->a, new_prompt, " $ ");
}

t_envl	*get_last_envl(t_envl *envl)
{
	if (!envl)
		return (NULL);
	while (envl->next)
		envl = envl->next;
	return (envl);
}
