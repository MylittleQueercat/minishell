/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprigent <aprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:04:43 by aprigent          #+#    #+#             */
/*   Updated: 2025/05/29 21:04:47 by aprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

char	*gnl(int fd);
char	*get_next_line(int fd);

char	*str_join(char *s1, const char *s2, int len);
int		nl_index(const char *str, int bytes);
int		clear(char *buff, int i);
#endif
