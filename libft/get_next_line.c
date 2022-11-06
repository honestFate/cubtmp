/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 00:13:33 by gtrinida          #+#    #+#             */
/*   Updated: 2022/11/01 00:13:37 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_clear_with_error(char **line)
{
	free(*line);
	*line = 0;
	return (-1);
}

char	*ft_get_remain(char **remain, char **line)
{
	char	*line_break;

	line_break = 0;
	if (*remain)
	{
		line_break = ft_strchr(*remain, '\n');
		if (line_break)
		{
			*line_break = '\0';
			*line = ft_strdup(*remain);
			ft_strcpy(*remain, line_break + 1);
		}
		else
		{
			*line = ft_strdup(*remain);
			free(*remain);
			*remain = 0;
		}
	}
	else
	{
		*line = malloc(sizeof(char));
		*line[0] = '\0';
	}
	return (line_break);
}

int	ft_reader(int fd, int *pos, char *buf)
{
	*pos = (int) read(fd, buf, BUFFER_SIZE);
	return (*pos);
}

char	*ft_strjoin_free(char **line, char *buf)
{
	char	*temp;

	temp = *line;
	*line = ft_strjoin(*line, buf);
	free(temp);
	if (!(*line))
		return (0);
	return (*line);
}

int	gnl(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	int				n_byte;
	char			*line_break;
	static char		*remain;

	n_byte = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	line_break = ft_get_remain(&remain, line);
	while (!line_break && ft_reader(fd, &n_byte, buf) > 0)
	{
		buf[n_byte] = '\0';
		line_break = ft_strchr(buf, '\n');
		if (line_break)
		{
			*line_break = '\0';
			remain = ft_strdup(line_break + 1);
		}
		*line = ft_strjoin_free(line, buf);
		if (!(*line))
			return (-1);
	}
	if (n_byte < 0)
		return (ft_clear_with_error(line));
	return ((n_byte || ft_strlen(*line)) && line_break);
}
