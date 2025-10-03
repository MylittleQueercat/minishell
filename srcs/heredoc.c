/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:26:06 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:06:10 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_delimiter(t_sh *sh, t_io_node *io, int i)
{
	char		**tmp;
	char		**del;

	del = NULL;
	while (++i >= 0 && io)
	{
		if (io->type != IO_HEREDOC)
		{
			io = io->next;
			continue ;
		}
		tmp = a_split(sh->a, io->raw_value, ' ');
		if (!tmp)
			return (NULL);
		del = a_realloc(sh->a, del, sizeof(char *) * i,
			sizeof(char *) * (i + 2));
		if (!del)
			return (NULL);
		del[i] = throw_quotes(sh, tmp[0]);
		if (!del[i])
			return (NULL);
		io = io->next;
	}
	if (del)
		del[i] = NULL;
	return (del);
}

void	heredoc_child(t_sh *sh, t_node *node, int fd, const char *delimiter)
{
	char	*line;

	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	dup2(sh->fd_stdout, STDOUT_FILENO);
	dup2(sh->fd_stdin, STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (node->io_list->quoted == 0)
			expand_heredoc(*sh, line, fd);
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
	}
	close(fd);
	exit((free_all(sh), 0));
}

void	heredoc_parent(t_sh *sh, int pid)
{
	int	status;

	(void)sh;
	wait_and_signal(pid, &status);
	if ((status & 0x7f) == SIGINT)
	{
		unlink(".heredoc_tmp");
		return (g_st = 130, ft_putstr_fd("\n", sh->fd_stdout), (void)0);
	}
	g_st = (status >> 8) & 0xff;
}

int	fork_heredoc(t_sh *sh, t_node *node)
{
	int		pid;
	int		fd;
	char	**delimiter;

	delimiter = get_delimiter(sh, node->io_list, -1);
	if (!delimiter)
		exit((perror("malloc"), free_all(sh), 1));
	while (delimiter && *delimiter)
	{
		fd = open(node->heredoc, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), close(fd), unlink(node->heredoc), 1);
		if (pid == 0)
			heredoc_child(sh, node, fd, *delimiter);
		else
			heredoc_parent(sh, pid);
		delimiter++;
		close(fd);
		if (g_st == 130)
			break ;
	}
	node->heredoc_fd = open(node->heredoc, O_RDONLY);
	if (node->heredoc_fd < 0)
		return (perror("open"), unlink(node->heredoc), 1);
	unlink(node->heredoc);
	return (g_st);
}

int	exec_heredoc(t_sh *sh, t_node *node)
{
	char	*file;

	while (node)
	{
		if (node->type != N_CMD)
		{
			if (exec_heredoc(sh, node->left) == 1)
				return (1);
			node = node->right;
		}
		else
			break ;
	}
	if (!node || !node->io_list || node->io_list->type != IO_HEREDOC)
		return (0);
	file = a_strdup(sh->a, ".heredoc_tmp");
	if (!file)
		exit((perror("malloc"), free_all(sh), 1));
	node->heredoc = a_strjoin(sh->a, file, a_itoa(sh->a, sh->heredoc_count--));
	if (!node->heredoc)
		exit((perror("malloc"), free_all(sh), 1));
	return (fork_heredoc(sh, node) != 0);
}
