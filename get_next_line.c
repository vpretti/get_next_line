/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpretti <vpretti@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:13:49 by vpretti           #+#    #+#             */
/*   Updated: 2022/05/27 15:20:23 by vpretti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			validate;
	char		*buffer;
	char		*line;
	static char	*accumulator;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	validate = 1;
	buffer = new_buffer();
	while ((!ft_strchr(accumulator, '\n')) && validate > 0)
	{
		validate = read(fd, buffer, BUFFER_SIZE);
		if (validate == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[validate] = '\0';
		accumulator = ft_strjoin(accumulator, buffer);
	}
	free(buffer);
	line = get_line(accumulator);
	accumulator = get_remainder(accumulator);
	return (line);
}

char	*new_buffer(void)
{
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	return (buffer);
}

char	*get_line(char *str)
{
	char	*line;
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[size] != '\n' && str[size])
		size++;
	if (str[size] == '\n')
		size++;
	line = (char *) malloc((size + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (str[i] != '\n' && str[i])
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_remainder(char *str)
{
	char	*remainder;
	int		i;
	int		s;

	i = 0;
	s = 0;
	if (!str || !str[i])
	{
		free(str);
		return (NULL);
	}
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	remainder = (char *)malloc((sizeof(char) * (ft_strlen(str) - i + 1)));
	if (!remainder)
		return (NULL);
	while (str[i])
		remainder[s++] = str[i++];
	remainder[s] = '\0';
	free(str);
	return (remainder);
}
