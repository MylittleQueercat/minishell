/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:47:07 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/17 14:11:41 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	int i;


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

int	is_builtin_cmd(const char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "env", 3) == 0 ||
		ft_strncmp(cmd, "pwd", 3) == 0 || ft_strncmp(cmd, "exit", 4) == 0 ||
		ft_strncmp(cmd, "cd", 2) == 0 || ft_strncmp(cmd, "export", 6) == 0 ||
		ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	return (0);
}

char	*build_prompt(const char *pwd)
{
	char	*prompt_str;

	if (!pwd)
		pwd = "~";
	prompt_str = ft_strjoin("\033[1;32mminishell:\033[0m ", pwd);
	if (!prompt_str)
		return (NULL);
	prompt_str = ft_strjoin(prompt_str, " $ ");
	return (prompt_str);
}

void	add_colors(t_env *env)
{
	char	*colors[3];
	t_cmd	cmd;

	colors[0] = "export";
	colors[1] = LS_COLORS;
	colors[2] = NULL;
	cmd.cmd = *colors;
	cmd.args = colors;
	ft_export(&cmd, env);
}

int count_args(char **args)
{
	int count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}
