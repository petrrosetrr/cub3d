/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:21:38 by jalease           #+#    #+#             */
/*   Updated: 2020/11/19 21:29:06 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if ((ptr = (unsigned char*)malloc(size * count)) != NULL)
	{
		while (i < size * count)
			ptr[i++] = '\0';
	}
	return (ptr);
}

int				ft_free(char **tbuf, int ret_value)
{
	if (*tbuf != NULL)
		free(*tbuf);
	*tbuf = NULL;
	return (ret_value);
}

long int		ft_read(int fd, char **tbuf)
{
	long int len;

	len = ft_strlen(*tbuf);
	if (ft_strrealloc(tbuf))
	{
		return (read(fd, *(tbuf) + len, BUFFER_SIZE));
	}
	return (-1);
}

int				get_next_line_2(char **tbuf, long int rs, int fd, char **line)
{
	long int n;

	if ((n = find_n(*tbuf)) > -1)
	{
		*line = ft_strndup(*tbuf, n);
		return (ft_strcut(tbuf, n + 1));
	}
	else
	{
		rs = ft_read(fd, tbuf);
		if (rs == 0)
		{
			*line = ft_strndup(*tbuf, ft_strlen(*tbuf));
			return (ft_free(tbuf, 0));
		}
		else if (rs == -1)
			return (ft_free(tbuf, -1));
	}
	return (2);
}

int				get_next_line(int fd, char **line)
{
	static char		*tbuf;
	int				n;
	long int		rs;

	while (1 && BUFFER_SIZE > 0 && fd >= 0)
	{
		if (tbuf == NULL)
		{
			rs = ft_read(fd, &tbuf);
			if (rs == 0)
			{
				*line = ft_strndup("", 0);
				return (ft_free(&tbuf, 0));
			}
			else if (rs == -1)
				return (ft_free(&tbuf, -1));
		}
		else
		{
			if ((n = get_next_line_2(&tbuf, rs, fd, line)) == 2)
				continue;
			return (n);
		}
	}
	return (-1);
}
