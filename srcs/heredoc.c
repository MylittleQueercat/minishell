/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:26:06 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/17 19:21:33 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(t_minishell *sh, t_node *node, int fd)
{
	char	*line;

	node->io_list->heredoc = 0;//Need to be set in parser if delimiter is quoted
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, node->cmd->infile) == 0)
		{
			free(line);
			break ;
		}
		if (node->io_list->heredoc == 0)
			expand_heredoc(*sh, line, fd);
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
	}
	close(fd);
	exit(0);
}

void	heredoc_parent(t_minishell *sh, t_node *node, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	close(node->cmd->in_fd);
	if ((status & 0x7f) == SIGINT)
	{
		unlink(".heredoc_tmp");
		sh->exit_s = 130;
		return ;
	}
	sh->exit_s = (status >> 8) & 0xff;
	g_sigstate.sigint_heredoc = false;
}

int	exec_heredoc(t_minishell *sh, t_node *node)
{
	int	pid;

	node->cmd->in_fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->cmd->in_fd < 0)
			return (perror("heredoc"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		heredoc_child(sh, node, node->cmd->in_fd);
	else
		heredoc_parent(sh, node, pid);
	if (sh->exit_s == 130)
		return (1);
	node->cmd->in_fd = open(".heredoc_tmp", O_RDONLY);
	if (node->cmd->in_fd < 0)
		return (perror("heredoc"), 1);
	unlink(".heredoc_tmp");
	return (0);
}
