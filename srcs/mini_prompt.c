/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:27:57 by hguo              #+#    #+#             */
/*   Updated: 2025/09/29 15:29:00 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_my_prompt(t_sh *sh, int continuation)
{
	char	cwd[4096];
	char	*prompt;
	char	*home;
	char	*display_path;

	if (continuation)
		return (a_strdup(sh->a, YELLOW BOLD "🟡 ↪ " RESET));
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "?", sizeof(cwd));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		display_path = a_strjoin(sh->a, "~", cwd + ft_strlen(home));
	else
		display_path = a_strdup(sh->a, cwd);
	prompt = a_strdup(sh->a, GREEN BOLD "🟢 INS " RESET PINK BOLD"📂 ");
	prompt = a_strjoin(sh->a, prompt, display_path);
	prompt = a_strjoin(sh->a, prompt, RESET " ❯ ");
	return (prompt);
}
