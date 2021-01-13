/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:29:49 by jalease           #+#    #+#             */
/*   Updated: 2020/11/03 16:33:40 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	size_t	size(long int n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static	char	*mem_alloc(size_t s)
{
	char *ptr;

	if ((ptr = malloc(s + 1)) != NULL)
	{
		return (ptr);
	}
	return (NULL);
}

static	char	*fill(char *ptr, long int n, int flag)
{
	*ptr = '\0';
	ptr--;
	if (n == 0)
	{
		*ptr = '0';
		return (ptr);
	}
	while (n)
	{
		*ptr = n % 10 + '0';
		n = n / 10;
		ptr--;
	}
	if (flag)
		ptr++;
	return (ptr);
}

char			*ft_itoa(int n)
{
	size_t		s;
	char		*ptr;
	long int	temp;

	temp = n;
	s = size(temp);
	if ((ptr = mem_alloc(s)) != NULL)
	{
		if (temp < 0)
		{
			*ptr = '-';
			ptr = fill(ptr + s, -1 * temp, 0);
		}
		else
			ptr = fill(ptr + s, temp, 1);
	}
	return (ptr);
}
