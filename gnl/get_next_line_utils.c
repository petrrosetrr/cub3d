/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 22:22:14 by jalease           #+#    #+#             */
/*   Updated: 2020/11/19 20:06:50 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t i;

	if (s != NULL)
	{
		i = 0;
		while (*(s + i) != 0)
			i++;
		return (i);
	}
	return (0);
}

char		*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if ((ptr = (char*)malloc(n + 1)) != NULL)
	{
		while (*s1 != 0 && i < n)
		{
			ptr[i] = *s1++;
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (NULL);
}

int			ft_strcut(char **tbuf, long int start)
{
	char		*temp;
	long int	i;

	i = ft_strlen(*tbuf);
	temp = *tbuf;
	if ((*tbuf = ft_calloc(i - start + 1, 1)) != NULL)
	{
		i = 0;
		while (temp[i + start] != '\0')
		{
			*(*tbuf + i) = temp[i + start];
			i++;
		}
		free(temp);
		return (1);
	}
	return (-1);
}

long int	find_n(char *str)
{
	long int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			ft_strrealloc(char **tbuf)
{
	char		*ptr;
	char		*tmp;
	long int	strsize;
	long int	i;
	int			n;

	i = 0;
	tmp = NULL;
	n = 1;
	strsize = ft_strlen(*tbuf);
	if ((ptr = ft_calloc(strsize + (BUFFER_SIZE
	> 10000000 ? 10000000 : BUFFER_SIZE) + n, 1)) != NULL)
	{
		while (strsize-- > 0)
		{
			ptr[i] = *(*tbuf + i);
			i++;
		}
		tmp = *tbuf;
		*tbuf = ptr;
		if (tmp != NULL)
			free(tmp);
		return (1);
	}
	return (0);
}
