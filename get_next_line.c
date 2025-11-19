/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjdia <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:14:35 by sjdia             #+#    #+#             */
/*   Updated: 2025/11/19 11:35:30 by sjdia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
     
#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*get_line(char *line)
{
	char		*left;
	ssize_t		i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[0] == '\0')
		return (NULL);
	left = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*left == 0)
	{
		free(left);
		left = NULL;
	}
	if (line[i] == '\n')
		line[i + 1] = '\0';
	return (left);
}

char	*fill_line(int fd, char *buf, char **left)
{
	char	*tmp;
	ssize_t	nb_read;

	nb_read = 1;
	while (nb_read > 0)
	{
		nb_read = read(fd, buf, (size_t)BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(*left);
			*left = NULL;
			return (NULL);
		}
		else if (nb_read == 0)
			break ;
		buf[nb_read] = '\0';
		tmp = *left;
		*left = ft_strjoin(*left, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (*left);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = fill_line(fd, buf, &left);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	left = get_line(line);
	return (line);
}
