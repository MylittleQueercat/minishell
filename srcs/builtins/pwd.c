/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:52:46 by aprigent          #+#    #+#             */
/*   Updated: 2025/09/30 13:10:55 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*pwd;
	char	*cwd;

	pwd = getenv("PWD");
	if (pwd && *pwd)
	{
		printf("%s\n", pwd);
		g_st = 0;
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		g_st = 1;
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
	g_st = 0;
}
