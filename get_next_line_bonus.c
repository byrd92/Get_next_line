/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:42:52 by egarcia-          #+#    #+#             */
/*   Updated: 2019/11/27 20:44:54 by egarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char			*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

static void			ft_strdel(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int					ft_putline(int fd, char **s, char **line)
{
	int		size;
	char	*tmp;

	size = 0;
	while (s[fd][size] != '\n')
		size++;
	*line = ft_substr(s[fd], 0, size);
	tmp = ft_strdup(&s[fd][size + 1]);
	free(s[fd]);
	s[fd] = tmp;
	return (1);
}

int					output(int ret, int fd, char **s, char **line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
	{
		*line = ft_strdup("");
		ft_strdel(&s[fd]);
		return (0);
	}
	else if (ft_strchr(s[fd], '\n'))
		return (ft_putline(fd, s, line));
	else
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
		return (0);
	}
}

int					get_next_line(int fd, char **line)
{
	int				ret;
	static char		*s[4096];
	char			*buff;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (!(buff = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	free(buff);
	return (output(ret, fd, s, line));
}
