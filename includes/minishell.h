/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:48:19 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/30 12:49:11 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "parse.h"
# include "mini_signal.h"
# include "arena.h"
# include <signal.h>
# include <stddef.h>
# include <stdbool.h>
# include <termios.h>
# include <dirent.h>
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

# define YELLOW      "\001\033[33m\002"
# define GREEN       "\001\033[32m\002"
# define CYAN        "\001\033[36m\002"
# define BOLD        "\001\033[1m\002"
# define RESET       "\001\033[0m\002"
# define PURPLE      "\001\033[35m\002"
# define ORANGE		"\001\033[38;5;208m\002"
# define PINK		"\001\033[38;2;255;105;180m\002"

extern int	g_st;

typedef struct s_envl
{
	char			*name;
	char			*value;
	struct s_envl	*next;
}	t_envl;

typedef struct s_env
{
	t_envl	*envl;
	char	**envp;
	char	*path;
	char	*pwd;
	char	*oldpwd;
}	t_env;

typedef struct s_sh
{
	char			*line;
	char			*prompt;
	t_token			*tokens;
	t_token			*current;
	t_node			*tree;
	t_parse_err		parse_err;
	t_env			*env;
	int				exit_s;
	int				exit_flag;
	int				**pipes;
	int				nb_pipes;
	int				fd_stdin;
	int				fd_stdout;
	t_arena			*sh_arena;
	t_arena			*a;
	struct termios	original_term;
}	t_sh;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				argc;
	char			*path;
	char			*infile;
	char			*outfile;
	int				in_fd;
	int				out_fd;
	int				type;
}	t_cmd;

// execution

t_sh	*setup_minishell(char **envp);
void	init_sh(t_sh *sh, char **envp);

t_env	*init_env(t_sh *sh, char **envp);

int		init_cmd(t_sh *sh, t_node *node);

void	free_all(t_sh *sh);

void	loop(t_sh *sh);

void	run_exec(t_sh *sh, t_node *node);
void	exec_cmd_or_builtin(t_sh *sh, t_node *node);
void	exec_builtin(t_sh *sh, t_cmd *cmd);
void	exec_cmd(t_sh *sh, t_cmd *cmd);
int		exec_heredoc(t_sh *sh, t_node *node);

void	fork_node(t_sh *sh, t_node *node);
void	child_process(t_sh *sh, t_node *node, int *fds, int n);

char	*get_cmd_path(t_sh *sh, char *path, t_cmd *cmd, int i);

void	build_prompt(t_sh *sh);
t_envl	*get_last_envl(t_envl *envl);
void	add_colors(t_sh *sh);
int		count_args(char **args);
void	setup_redirections(t_cmd *cmd);
void	increment_shlvl(t_sh *sh);

void	loop(t_sh *sh);

int		is_builtin(const char *cmd);
int		is_builtin_output(const char *cmd);

void	print_sorted_env(t_env *env, int flag);
int		is_valid_identifier(const char *str);
int		var_exists(t_env *env, const char *var);
int		update_envp(t_sh *sh, t_env *env);
void	change_env_var(t_sh *sh, t_env *env, const char *var);
char	*get_env_value(const char *name, char **envp);

void	ft_env(t_cmd *cmd, t_env *env);
void	ft_echo(t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(t_sh *sh, t_cmd *cmd, t_env *env);
void	ft_export(t_sh *sh, t_cmd *cmd);
void	ft_unset(t_sh *sh, t_cmd *cmd, t_env *env);
void	ft_exit(t_sh *sh, t_cmd *cmd);
// parsing
//
//
/* Expander */
// expand_util.c
char	*get_env_val(t_sh *sh, char *var);
int		is_valid_var_char(char c);
char	*clean_empty(t_sh *sh, char *str);

// expand_split.c
char	**expand_split(t_sh *sh, char const *str);

// expand_pre_handle.c
char	*handle_squotes(t_sh *sh, char *str, size_t *i);
char	*get_env_val(t_sh *sh, char *var);
char	*handle_dollar(t_sh *sh, char *str, size_t *i);
char	*handle_dquotes(t_sh *sh, char *str, size_t *i);
char	*handle_normal(t_sh *sh, char *str, size_t *i);

// globber_util.c
int		is_with_asterisk(char *str);
size_t	get_str_arr_len(char **str_arr);
size_t	match_count(char *pattern);
char	**join_str_arr(t_sh *sh, char ***str_arr);

// expand_globber.c
int		is_with_asterisk(char *str);
int		match_vis(char *pattern, char *str);
int		set_direntry(struct dirent **entry, DIR *dir);
char	**expand_globber(t_sh *sh, char **expanded);

// throw_quotes.c
char	*throw_quotes(t_sh *sh, char *str);

// expand_aterisker.c
bool	check_star(char *mask, char *str);

// expand_heredoc.c
void	expand_heredoc(t_sh sh, char *str, int fd);

// expand.c
void	expander(t_sh *sh, t_node *node);
//int		expand_tree(t_sh *sh, t_node *node);

/* clean */
void	clean_message(t_sh *sh);

/* prompt */
char	*make_my_prompt(t_sh *sh, int continuation);

#endif /* MINISHELL_H */
