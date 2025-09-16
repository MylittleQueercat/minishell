/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:47:07 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/16 18:38:44 by aprigent         ###   ########.fr       */
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

void	build_prompt(t_minishell *sh)
{
	char	*new_prompt;

	if (!sh->env->pwd)
		sh->env->pwd = ft_strdup("~");
	new_prompt = ft_strjoin("\033[1;32mminishell:\033[0m ", sh->env->pwd);
	if (!new_prompt)
		return ;
	free(sh->prompt);
	sh->prompt = ft_strjoin(new_prompt, " $ ");
	free(new_prompt);
}

t_envl	*get_last_envl(t_envl *envl)
{
	if (!envl)
		return (NULL);
	while (envl->next)
		envl = envl->next;
	return (envl);
}

char	*strjoin_free_s1(char *s1, char *s2)
{
	char	*joined;

	if (!s1)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	print_io_list(t_io_node *io)
{
	while (io)
	{
		printf("IO type: %d, raw value: %s\n", io->type, io->raw_value);
		if (io->exec_value)
		{
			printf("  Exec values: ");
			for (int i = 0; io->exec_value[i]; i++)
				printf("'%s' ", io->exec_value[i]);
			printf("\n");
		}
		io = io->next;
	}
}

int	init_cmd(t_minishell *sh, t_node *node)
{
	t_cmd	*cmd;

	node->cmd = malloc(sizeof(t_cmd));
	if (!node->cmd)
		return (perror("malloc"), -1);
	cmd = node->cmd;
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->cmd = node->exec_args[0];
	cmd->args = node->exec_args;
	cmd->out_fd = -1;
	cmd->in_fd = -1;
	parse_io(node, cmd);
	if (cmd->type == IO_HEREDOC)
		exec_heredoc(sh, cmd, cmd->in_fd);
	return (0);
}
