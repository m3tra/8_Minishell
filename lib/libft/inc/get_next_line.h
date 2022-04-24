/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:28:07 by fporto            #+#    #+#             */
/*   Updated: 2022/01/26 05:16:27 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# define FD_MAX 4096

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>

int		get_next_line(int fd, char **line);
int		save_lines(char **lineread, char *buffer, char **line, \
	ssize_t nreadbytes);

#endif
