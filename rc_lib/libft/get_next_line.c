/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <tvallee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 15:14:30 by tvallee           #+#    #+#             */
/*   Updated: 2015/01/15 15:48:01 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_canyoufillit(char *s, t_buff *buff, int i)
{
	char	temp;
	int		j;

	temp = *(buff->buff + buff->offst + i);
	s[i] = 0;
	j = 0;
	while (j < i)
	{
		s[j] = *(buff->buff + buff->offst + j);
		j++;
	}
	buff->offst = buff->offst + j + 1;
	if (temp == 10)
		return (2);
	return (1);
}

static int		ft_anfill(char **s, t_buff *buff)
{
	int		i;
	char	*ns;

	i = 0;
	while (*(buff->buff + buff->offst + i) != 10 &&
			buff->offst + i < buff->readret)
		i++;
	ns = malloc(sizeof(char) * (i + ft_strlen(*s) + 1));
	if (!ns)
		return (3);
	ft_strcpy(ns, (const char*)*s);
	free(*s);
	*s = ns;
	return (ft_canyoufillit(*s + ft_strlen(*s), buff, i));
}

static t_buff	*ft_init(int fd, t_buff **list)
{
	t_buff	*old;
	t_buff	*current;

	old = NULL;
	current = *list;
	while (current && current->fd != fd && (old = current))
		current = current->next;
	if (current != NULL)
		return (current);
	if ((current = ft_memalloc(sizeof(t_buff))))
	{
		if (!(current->buff = ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (NULL);
		current->fd = fd;
		current->readret = 1;
		if (old)
			old->next = current;
		else
			*list = current;
	}
	return (current);
}

static int		ft_end(t_buff **list, int fd, int ret, int offset)
{
	t_buff	*old;
	t_buff	*current;

	old = NULL;
	current = *list;
	if (ret != 2)
	{
		while (current->fd != fd)
		{
			old = current;
			current = current->next;
		}
		if (!old)
			*list = current->next;
		else
			old->next = (current->next) ? current->next : NULL;
		free(current->buff);
		free(current);
	}
	return (offset);
}

int				get_next_line(int const fd, char **line)
{
	static t_buff	*list;
	t_buff			*buff;
	char			*s;
	int				ret;

	if (!line || (buff = ft_init(fd, &list)) == NULL || buff->readret < 0)
		return (-1);
	s = malloc(1);
	*s = 0;
	while (buff->readret > 0)
	{
		ret = ft_anfill(&s, buff);
		if (ret == 1)
		{
			buff->readret = read(fd, buff->buff, BUFF_SIZE);
			buff->offst = 0;
		}
		else if (ret == 2)
			break ;
		if (buff->readret < 0 || ret == 3)
			return (-1);
	}
	*line = s;
	return (*s || ft_end(&list, fd, ret, buff->offst) != 0) ? 1 : 0;
}
