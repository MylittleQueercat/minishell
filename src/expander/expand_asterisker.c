#include "minishell.h"

static	void	handle_mask_quotes(char **mask, char *quotes)
{
	if (**mask == '"' || **mask == '\'')
		*quotes = *(*mask)++;
	else
	{
		if (*quotes == **mask)
		{
			*quotes = 0;
			(*mask)++;
		}
	}
}

static	bool	handle_stars(char **mask, char **last_wildcard, char **last_match, char *str)
{
	while (**mask == '*')
		(*mask)++;
	if (!**mask)
		return (true);
	*last_wildcard = *mask;
	*last_match = str;
	return (false);
}

static	bool	try_match(char **mask, char **last_wildcard, char **last_match, char *str)
{
	if (**mask == **str)
	{
		(*mask)++;
		(*str)++;
		return (true);
	}
	else if (*last_wildcard)
	{
		*str = ++(last_match);
		*mask = *last_wildcard;
		return (true);
	}
	else
		return (false);
}	

bool	check_star(char *mask, char *str)
{
	char	*last_wildcard;
	char	*last_match;
	char	quotes;

	quotes = 0;
	last_wildcard = NULL;
	last_match = NULL;
	while (*str)
	{
		handle_mask_quotes(&mask, &quotes);
		if (*mask == '*' && !quotes
			&& handle_stars(&mask, &last_wildcard, &last_match, str))
			return (true);
		else if (!try_match(&mask, &last_wildcard, &last_match, &str))
			return (false);
	}
	if (*pattern == '*')
		while (*pattern == '*')
			pattern++;
	return (!*pattern);
}
