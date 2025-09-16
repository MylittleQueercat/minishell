/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:26:06 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/16 18:38:49 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_heredoc(t_minishell *sh, t_cmd *cmd, int fd)
{
	char	*line;

	while 1)
	{
		line = readline("> ");
		expand_heredoc(*sh, line, fd);
		if (!line || ft_strcmp(line, cmd->infile) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}
