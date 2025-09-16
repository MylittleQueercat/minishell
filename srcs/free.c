/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 00:41:21 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/16 15:20:57 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_env(t_env *env)
{
	t_envl	*current;
	t_envl	*next;

	if (!env)
		return ;
	current = env->envl;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	free_array(env->envp);
	free(env->path);
	free(env->pwd);
	free(env->oldpwd);
	free(env);
}

void	free_minishell(t_minishell *sh)
{
	if (!sh)
		return ;
	if (sh->pipes)
		free_pipes(sh->pipes, sh->nb_pipes + 1);
	if (sh->env)
		free_env(sh->env);
	if (sh->fd_stdin != -1)
		close(sh->fd_stdin);
	if (sh->fd_stdout != -1)
		close(sh->fd_stdout);
	if (sh->prompt)
		free(sh->prompt);
	clear_ast_token(sh);
	rl_clear_history();
	if (sh->line)
		free(sh->line);
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->original_term);
	free(sh);
}

void	free_pipes(int **pipes, int n)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < n - 1)
		free(pipes[i++]);
	free(pipes);
}
