/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:04:57 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/29 21:04:58 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl(int fd)
{
	return (get_next_line(fd));
}

char	*get_next_line(int fd)
{
	static char	buff[1024][BUFFER_SIZE + 1];
	char		*line;
	int			b;
	int			i;
	int			j;

	if (fd < 0 || fd > 1023)
		return (NULL);
	free((j = -1, line = NULL, b = BUFFER_SIZE, NULL));
	while (nl_index(buff[fd], b) == -1)
	{
		line = str_join(line, buff[fd], BUFFER_SIZE);
		b = read(fd, buff[fd], BUFFER_SIZE);
		if (clear(buff[fd], b) && (b < 0 || !line || (!b && !*line)))
			return (clear(buff[fd], 0), free(line), NULL);
	}
	i = nl_index(buff[fd], b);
	line = str_join(line, buff[fd], i);
	while (buff[fd][++j + i])
		buff[fd][j] = buff[fd][j + i];
	buff[fd][j] = 0;
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}
