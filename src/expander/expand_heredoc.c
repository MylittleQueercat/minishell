#include "minishell.c"

void	*go_trash(void *ptr, bool clean)
{
	static t_list	*list;

	if (!clean)
	{
		ft_lstadd_back(&list, ft_lstnew(ptr));
		return (ptr);
	}
}

static	int	expand_heredoc_printer(t_minishell sh, char *str, size_t i; int fd)
{
	size_t	start;
	char	*tmp;

	start = ++i;
	if (str[i] == '?')
		return (ft_putnbr_fd(sh.exit_s, fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = go_trash(ft_substr(str, start, i), false);
		tmp = get_envlst_val(tmp);
		if (tmp)
			ft_putstr_fd(tmp, fd);
	}
	return (i);
}

void	expand_heredoc(t_minishell sh, char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += expand_heredoc_printer(sh, str, i ,fd);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}
