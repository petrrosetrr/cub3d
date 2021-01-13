/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:29:24 by jalease           #+#    #+#             */
/*   Updated: 2020/11/07 00:31:41 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_amount(char const *s, char c)
{
	unsigned short int	flag;
	size_t				i;

	flag = 0;
	i = 0;
	while (*s != 0)
	{
		if (*s != c && !flag)
		{
			i++;
			flag = 1;
		}
		else if (*s == c)
		{
			flag = 0;
		}
		s++;
	}
	return (i);
}

static size_t	ft_wlen(char **ptr, char c)
{
	int		flag;
	size_t	i;

	i = 0;
	flag = 0;
	while (**ptr != 0)
	{
		if (**ptr == c && flag)
			return (i);
		else if (**ptr != c)
		{
			i++;
			flag = 1;
		}
		(*ptr)++;
	}
	if (**ptr == 0 && flag)
	{
		return (i);
	}
	return (0);
}

static char		*ft_strndup(const char *s1, size_t n)
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

char			**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	amount;
	size_t	len;

	if (s != NULL)
	{
		amount = ft_amount(s, c);
		if ((arr = (char**)malloc(amount * sizeof(char*)
		+ sizeof(char*))) != NULL && (i = 0) == 0)
		{
			while (i < amount)
			{
				len = ft_wlen((char**)&s, c);
				if ((arr[i] = ft_strndup(s - len, len)) == NULL)
				{
					return (NULL);
				}
				i++;
			}
			arr[i] = NULL;
			return (arr);
		}
	}
	return (NULL);
}
