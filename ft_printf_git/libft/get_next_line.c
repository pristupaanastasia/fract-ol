/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:07:06 by smanhack          #+#    #+#             */
/*   Updated: 2019/04/18 15:05:46 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_list	*ft_give_lst(t_list **all_fd, int fd)
{
	t_list	*buff;
	t_file	line_fd;

	line_fd.fd = fd;
	if (!(*all_fd))
	{
		*all_fd = ft_lstnew(&line_fd, sizeof(line_fd));
		((t_file *)(*all_fd)->content)->line = ft_strnew(0);
		return (*all_fd);
	}
	buff = *all_fd;
	while (buff->next && ((t_file *)buff->content)->fd != line_fd.fd)
		buff = buff->next;
	if (((t_file *)buff->content)->fd == fd)
		return (buff);
	buff->next = ft_lstnew(&line_fd, sizeof(line_fd));
	((t_file *)(buff->next)->content)->line = ft_strnew(0);
	return (buff->next);
}

static int		ft_lst_free(t_list **all_fd, int fd)
{
	t_list	*tmp;
	t_list	*buf;

	tmp = *all_fd;
	if (((t_file *)tmp->content)->fd == fd)
	{
		free(((t_file *)(tmp)->content)->line);
		free((tmp)->content);
		*all_fd = tmp->next;
		free(tmp);
		return (0);
	}
	while (((t_file *)tmp->next->content)->fd != fd)
		tmp = tmp->next;
	if (tmp)
	{
		buf = tmp->next;
		tmp->next = buf->next;
		free(((t_file *)(buf)->content)->line);
		free((buf)->content);
		free(buf);
	}
	return (0);
}

static t_list	*ft_find_fd(t_list **all_fd, int fd)
{
	t_list *buff;

	buff = *all_fd;
	while (((t_file *)buff->content)->fd != fd)
		buff = buff->next;
	return (buff);
}

static int		ft_line(t_list **all_fd, char **line, int fd)
{
	char	*buf;
	t_file	*buf_lst;
	size_t	len;
	char	*buf_str;

	buf_lst = (t_file *)ft_find_fd(all_fd, fd)->content;
	if (*(buf_lst->line) == '\0')
		return (ft_lst_free(all_fd, fd));
	len = ft_strlen(buf_lst->line);
	if ((buf_str = ft_strchr(buf_lst->line, '\n')) != NULL)
	{
		*buf_str = '\0';
		*line = ft_strdup(buf_lst->line);
		buf = ft_strdup(buf_str + 1);
		free(buf_lst->line);
		buf_lst->line = ft_strdup(buf);
		free(buf);
	}
	else
	{
		*line = ft_strdup((buf_lst)->line);
		ft_lst_free(all_fd, fd);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ref;
	static t_list	*all_fd;
	t_file			*buf_lst;
	char			*tmp;

	if (fd < 0 || !line || BUFF_SIZE < 1 ||
	BUFF_SIZE >= 10000000 || read(fd, buf, 0) < 0)
		return (-1);
	buf_lst = (t_file *)ft_give_lst(&all_fd, fd)->content;
	while (ft_strchr(buf_lst->line, '\n') == NULL &&
	(ref = read(fd, buf, BUFF_SIZE)))
	{
		buf[ref] = '\0';
		tmp = ft_strjoin(buf_lst->line, buf);
		free(buf_lst->line);
		buf_lst->line = ft_strdup(tmp);
		free(tmp);
	}
	return (ft_line(&all_fd, line, fd));
}
