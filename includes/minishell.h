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
	char	**export;
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
	int				**pipes;
	int				fd_stdin;
	int				fd_stdout;
	struct termios	original_term;
}	t_minishell;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*path;
	char			*input_file;
	char			*output_file;
	int				*pipes;
	int				type;
}	t_cmd;

// execution

void	init_minishell(t_minishell *sh, char **envp);

t_env	*init_env(char **envp);

void	free_minishell(t_minishell *sh);
void	free_env(t_env *env);
void	free_array(char **arr);
void	free_pipes(int **pipes, int n);

void	run_exec(t_minishell *sh);
void	run_iteration(t_minishell *sh);

int		exec_builtin(t_cmd *cmd, t_env *env);
int		exec_cmd(t_cmd *cmd, t_env *env, int i, int n);
int		exec_pipe(t_node *tree, t_env *env);
int		execute_pipeline(t_minishell *sh, t_node *node, int i, int nb_pipes);
void	setup_pipe(int *pipes, int i, int n, t_cmd *cmd);

int		count_pipes(t_node *node);

char	*get_cmd_path(char *path, char *cmd);

void	build_prompt(t_minishell *sh);
t_envl	*get_last_envl(t_envl *envl);
char	*strjoin_free_s1(char *s1, char *s2);

void	perror_exit(const char *msg, void (*fn)(t_env *), t_env *arg);

void	loop(t_minishell *sh);

int		is_builtin(const char *cmd);
int		exec_builtin(t_cmd *cmd, t_env *env);

void	print_export(t_env *env);

int		ft_env(t_cmd *cmd, t_env *env);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_cd(t_cmd *cmd, t_env *env);
int		ft_export(t_cmd *cmd, t_env *env);
int		ft_unset(t_cmd *cmd, t_env *env);

void	print_ast(t_node *node);

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
