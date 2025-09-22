/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:46:06 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/20 08:06:00 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_output(const char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "env", 3) == 0 ||
		ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	return (0);
}

void	add_colors(t_sh *sh)
{
	char	*colors[3];
	t_cmd	cmd;

	colors[0] = "export";
	colors[1] = LS_COLORS;
	colors[2] = NULL;
	cmd.cmd = *colors;
	cmd.args = colors;
	ft_export(sh, &cmd);
}

void	setup_redirections(t_cmd *cmd)
{
	if (cmd->in_fd != -1)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	if (cmd->out_fd != -1)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
}

void	increment_shlvl(t_sh *sh)
{
	int		i;
	char	*shlvl;

	shlvl = get_env_value("SHLVL", sh->env->envp);
	if (!shlvl)
	{
		shlvl = a_strdup(sh->sh_arena, "SHLVL=1");
		if (!shlvl)
			exit((perror("malloc"), free_all(sh), 1));
		return (change_env_var(sh, sh->env, shlvl), (void)0);
	}
	i = ft_atoi(shlvl);
	if (i < 0)
		i = 0;
	if (i >= 1000)
		printf("warning: shell level (%d) too high, resetting to 1\n", i);
	if (i >= 1000)
		i = 1;
	shlvl = a_itoa(sh->sh_arena, i + 1);
	if (!shlvl)
		exit((perror("malloc"), free_all(sh), 1));
	shlvl = a_strjoin(sh->sh_arena, "SHLVL=", shlvl);
	if (!shlvl)
		exit((perror("malloc"), free_all(sh), 1));
	change_env_var(sh, sh->env, shlvl);
}
