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
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "get_next_line.h"

# define CMD_BUILTIN 0
# define CMD_EXTERNAL 1
# define CMD_PIPE 2

typedef struct s_cmd
{
	char			*cmd;       // Command to execute
	char			**args;      // Arguments for the command
	char			*path;      // Path to the command
	char			*input_file; // Input redirection file
	char			*output_file; // Output redirection file
	int				input_fd;   // File descriptor for input redirection
	int				output_fd;  // File descriptor for output redirection
	int				type;
}	t_cmd;

typedef struct s_env
{
	char			**envp;		// Original environment variables
	char			**export;	 // Exported environment variables
	char			*path;		 // PATH environment variable
	char			*pwd;       // Current working directory
}	t_env;

typedef struct s_split
{
	int		i;			// Current index in the input string
	int		j;			// Current index in the result array
	int		k;			// Start index of the current word
	int		in_quotes;	// Flag to indicate if we are inside quotes
}	t_split;

t_env	*init_env(char **envp);
void	free_env(t_env *env);

int		exec_builtin(t_cmd *cmd, t_env *env);
int		exec_external(t_cmd *cmd, t_env *env);
int		exec_pipe(t_cmd *cmd, t_env *env);
char	*get_cmd_path(char *path, char *cmd);

void	free_array(char **arr);
int		is_builtin_cmd(const char *cmd);
char	*build_prompt(const char *pwd);
char	**split_input(const char *str);

void	loop(t_env *env);

int		is_builtin(const char *cmd);
int		exec_builtin(t_cmd *cmd, t_env *env);

void	print_export(t_env *env);

int		ft_env(t_cmd *cmd, t_env *env);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_cd(t_cmd *cmd, t_env *env);
int		ft_export(t_cmd *cmd, t_env *env);
int		ft_unset(t_cmd *cmd, t_env *env);
#endif /* MINISHELL_H */


