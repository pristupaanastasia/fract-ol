/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 13:40:45 by smanhack          #+#    #+#             */
/*   Updated: 2019/09/20 18:11:29 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1

# include <libc.h>
# include "libft.h"

typedef struct		s_file
{
	int				fd;
	char			*line;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
