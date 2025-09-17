/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:48:19 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/09 20:08:43 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "parse.h"
# include "mini_signal.h"
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

#define LS_COLORS "LS_COLORS=di=34:ln=36:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=37;41:sg=30;43:tw=30;42:ow=34;42"

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

typedef struct s_minishell
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
	struct termios	original_term;
}	t_minishell;

typedef struct s_cmd
{
	char			*cmd;       // Command to execute
	char			**args;      // Arguments for the command
	int				argc;
	char			*path;      // Path to the command
	char			*infile;
	char			*outfile;
	int				in_fd;
	int				out_fd;
	int				type;
}	t_cmd;

// execution

void	init_minishell(t_minishell *sh, char **envp);

t_env	*init_env(char **envp);

int		init_cmd(t_minishell *sh, t_node *node);

void	free_minishell(t_minishell *sh);
void	free_env(t_env *env);
void	free_array(char **arr);
void	free_pipes(int **pipes, int n);
void	free_tree(t_node *node);

void	clear_ast_token(t_minishell *sh);

void	run_exec(t_minishell *sh);
void	run_iteration(t_minishell *sh);

int		exec_cmd_or_builtin(t_minishell *sh, t_node *node, int i, int n);
int		exec_builtin(t_minishell *sh, t_cmd *cmd);
int		exec_cmd(t_minishell *sh, t_cmd *cmd, int i, int n);
int		exec_pipe(t_node *tree, t_env *env);
int		exec_pipeline(t_minishell *sh, t_node *node, int *i, int nb_pipes);
int		exec_heredoc(t_minishell *sh, t_node *node);
void	setup_pipes(int **pipes, int i, int n, t_cmd *cmd);
void	close_pipes(int **pipes, int i, int n);
void	close_all_pipes(int **pipes, int i, int n);

int		count_pipes(t_node *node);

char	*get_cmd_path(char *path, t_cmd *cmd, int i);

void	build_prompt(t_minishell *sh);
t_envl	*get_last_envl(t_envl *envl);
char	*strjoin_free_s1(char *s1, char *s2);
long long	ft_atoll(const char *str);
void	add_colors(t_minishell *sh);
int		count_args(char **args);

void	perror_exit(const char *msg, void (*fn)(t_env *), t_env *arg);

void	loop(t_minishell *sh);

int		is_builtin(const char *cmd);
int		is_builtin_output(const char *cmd);

void	print_sorted_env(t_env *env);
int		is_valid_identifier(const char *str);
int		var_exists(t_env *env, const char *var);
int		update_envp(t_env *env);
void	change_env_var(t_env *env, const char *var);
char	*get_env_value(const char *name, char **envp);

int		ft_env(t_cmd *cmd, t_env *env);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_cd(t_cmd *cmd, t_env *env);
int		ft_export(t_minishell *sh, t_cmd *cmd);
int		ft_unset(t_cmd *cmd, t_env *env);
int		ft_exit(t_minishell *sh, t_cmd *cmd, char *m);
// parsing
//
//
/* Expander */
// expand_util.c
char	*clean_empty(char *str);
char	*get_env_val(t_minishell *sh, char *var);
int		is_valid_var_char(char c);

// expand_split.c
char	**expand_split(char const *str);

// expand_pre_handle.c
char	*handle_squotes(char *str, size_t *i);
char	*get_env_val(t_minishell *sh, char *var);
char	*handle_dollar(t_minishell *sh, char *str, size_t *i);
char	*handle_dquotes(t_minishell *sh, char *str, size_t *i);
char	*handle_normal(char *str, size_t *i);

// globber_util.c
int		is_with_asterisk(char *str);
size_t	get_str_arr_len(char **str_arr);
size_t	match_count(char *pattern);
void	free_char_arr3(char	***to_free);
char	**join_str_arr(char ***str_arr);

// expand_globber.c
int		is_with_asterisk(char *str);
int		match_vis(char *pattern, char *str);
int		set_direntry(struct dirent **entry, DIR *dir);
char	**expand_globber(char **expanded);

// throw_quotes.c
char	*throw_quotes(char *str);

// expand_aterisker.c
bool	check_star(char *mask, char *str);

// expand_heredoc.c
void	*go_trash(void *ptr, bool clean);
void	expand_heredoc(t_minishell sh, char *str, int fd);

// expand.c
char	*ft_strjoin_free(char *s1, char *s2);
void	free_globbed(char **v);
void	expander(t_minishell *sh, t_node *node);
//int		expand_tree(t_minishell *sh, t_node *node);

/* clean */
void	clean_message(t_minishell *sh);

#endif /* MINISHELL_H */
