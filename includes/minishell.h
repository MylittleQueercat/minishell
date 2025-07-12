/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:48:19 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/12 14:51:11 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <wait.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"

# define CMD_BUILTIN 0
# define CMD_EXTERNAL 1
# define CMD_PIPE 2

typedef struct s_cmd
{
	char			*cmd;       // Command to execute
	char			**args;      // Arguments for the command
	char			*input_file; // Input redirection file
	char			*output_file; // Output redirection file
	int				input_fd;   // File descriptor for input redirection
	int				output_fd;  // File descriptor for output redirection
	int				type;
}	t_cmd;

typedef struct s_env
{
	char			**envp;
	char			*path;
}	t_env;

int	exec_cmd(t_cmd *cmd, t_env *env);
char	*get_path(t_env *env, char *cmd);
void	free_array(char **arr);

#endif /* MINISHELL_H */
