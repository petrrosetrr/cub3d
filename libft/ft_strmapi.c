/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:34:58 by jalease           #+#    #+#             */
/*   Updated: 2020/11/03 16:49:18 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (s != NULL && f != NULL)
	{
		while (s[i] != '\0')
		{
			i++;
		}
		if ((ptr = malloc(i + 1)))
		{
			ptr[i] = '\0';
			i = 0;
			while (s[i] != '\0')
			{
				ptr[i] = (*f)(i, s[i]);
				i++;
			}
			return (ptr);
		}
	}
	return (NULL);
}
