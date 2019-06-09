/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:54:03 by eskeleto          #+#    #+#             */
/*   Updated: 2019/06/07 14:23:10 by eskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_new_line(char **s, char **line, int fd, int ret)
{
	char	*tmp;
	int		len;

	len = 0;
	while (s[0][len] != '\n' && s[0][len] != '\0')
		len++;
	if (s[0][len] == '\n')
	{
		*line = ft_strsub(s[0], 0, len);
		tmp = ft_strdup(s[0] + len + 1);
		free(s[0]);
		s[0] = tmp;
		if (s[0][0] == '\0')
			ft_strdel(&s[0]);
	}
	else if (s[0][len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[0]);
		ft_strdel(&s[0]);
	}
	return (1);
}

static int	ft_read_file(int fd, char **sfile, char **line)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (*sfile == NULL)
			*sfile = ft_strnew(1);
		tmp = ft_strjoin(*sfile, buf);
		free(*sfile);
		*sfile = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (*sfile == NULL || *sfile[0] == '\0'))
		return (0);
	return (ft_new_line(sfile, line, fd, ret));
}

int			get_next_line(const int fd, char **line)
{
	static char	*sfile = NULL;
	char		str[1];

	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL || read(fd, str, 0) == -1)
		return (-1);
	return (ft_read_file(fd, &sfile, line));
}
