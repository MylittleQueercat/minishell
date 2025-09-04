/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leticiabi <leticiabi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:54 by hguo              #+#    #+#             */
/*   Updated: 2025/09/04 16:23:08 by leticiabi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "libft.h"
# include "parse.h"
# include "signal.h"
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char		*line;
	t_token		*tokens;
	t_token		*current;
	t_node		*tree;
	t_parse_err	parse_err;
	t_env		*envlst;
	int			exit_s;
	int			fd_stdin;
	int			fd_stdout;
	struct termios original_term;
}	t_minishell;

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
char	**expander(t_minishell *sh, char *str);

/* clean */
void	clean_message(t_minishell *sh);


#endif
