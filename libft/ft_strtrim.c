/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:37:54 by jalease           #+#    #+#             */
/*   Updated: 2020/11/03 16:49:57 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	get_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		flag;

	if (s1 != NULL && set != NULL)
	{
		i = 0;
		while (s1[i] != 0)
		{
			j = 0;
			flag = 1;
			while (set[j] != '\0')
			{
				if (s1[i] == set[j])
					flag = 0;
				j++;
			}
			if (flag)
				return (i);
			i++;
		}
	}
	return (0);
}

static size_t	get_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		flag;

	if (s1 != NULL && set != NULL)
	{
		i = ft_strlen(s1) - 1;
		while (i > 0)
		{
			j = 0;
			flag = 1;
			while (set[j] != '\0')
			{
				if (s1[i] == set[j])
					flag = 0;
				j++;
			}
			if (flag)
				return (i);
			i = i - 1;
		}
	}
	return (0);
}

static char		*new_str(char const *s1, size_t start, size_t end)
{
	char	*ptr;
	size_t	i;
	size_t	size;

	i = 0;
	if ((size = end - start + 2) <= 2)
		size = 1;
	if ((ptr = malloc(size)) != NULL)
	{
		while (i < size - 1)
		{
			ptr[i] = s1[start + i];
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (NULL);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t start;
	size_t end;

	if (s1 != NULL && set != NULL)
	{
		end = get_end(s1, set);
		start = get_start(s1, set);
		return (new_str(s1, start, end));
	}
	return (NULL);
}
