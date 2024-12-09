/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsilva <amsilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:36:52 by amsilva           #+#    #+#             */
/*   Updated: 2024/12/09 13:56:39 by amsilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buf, char *back)
{
	int		readl;
	char	*tmp;

	readl = 1;
	while (readl != '\0')
	{
		readl = read(fd, buf, BUFFER_SIZE);
		if (readl == -1)
			return (0);
		else if (readl == 0)
			break ;
		buf[readl] = '\0';
		if (!back)
			back = ft_strdup("");
		tmp = back;
		back = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (back);
}

static char	*split_line(char *line)
{
	char	*b;
	size_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (0);
	b = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*b == '\0')
	{
		free(b);
		b = NULL;
	}
	line[i + 1] = '\0';
	return (b);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*b;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = read_line(fd, buf, b);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	b = split_line(line);
	return (line);
}
