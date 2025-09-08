/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:48:19 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/02 19:14:17 by aprigent         ###   ########.fr       */
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
	int				argc;       // Number of arguments
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
	char			*oldpwd;    // Previous working directory
	int				exit_status;
}	t_env;

typedef struct s_split
{
	int		i;			// Current index in the input string
	int		j;			// Current index in the result array
	int		k;			// Start index of the current word
	int		in_quotes;	/* Flag to indicate if we are inside quotes */
}	t_split;

#define LS_COLORS "LS_COLORS=di=34:ln=36:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=37;41:sg=30;43:tw=30;42:ow=34;42"

t_env		*init_env(char **envp);
void		free_env(t_env *env);

int			exec_builtin(t_cmd *cmd, t_env *env);
int			exec_external(t_cmd *cmd, t_env *env);
int			exec_pipe(t_cmd *cmd, t_env *env);
char		*get_cmd_path(char *path, t_cmd *cmd);

void		free_array(char **arr);
int			is_builtin_cmd(const char *cmd);
char		*build_prompt(const char *pwd);
char		**split_input(const char *str);

int			loop(t_env *env);

int			is_builtin(const char *cmd);
int			exec_builtin(t_cmd *cmd, t_env *env);

void		print_export(t_env *env);

int			ft_env(t_cmd *cmd, t_env *env);
int			ft_echo(t_cmd *cmd);
int			ft_pwd(t_cmd *cmd);
int			ft_cd(t_cmd *cmd, t_env *env);
int			ft_export(t_cmd *cmd, t_env *env);
int			ft_unset(t_cmd *cmd, t_env *env);
int			ft_exit(t_cmd *cmd, t_env *env);

int			count_args(char **args);
void		add_colors(t_env *env);
long long	ft_atoll(char *str);

char		*get_env_value(const char *var, char **envp);
void		update_env_value(const char *var, const char *value, t_env *env);

#endif /* MINISHELL_H */
