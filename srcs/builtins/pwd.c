/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:52:46 by aprigent          #+#    #+#             */
/*   Updated: 2025/07/17 12:55:23 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;

	if (cmd->args[1])
	{
		printf("pwd: '%s': No such file or directory\n", cmd->args[1]);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
