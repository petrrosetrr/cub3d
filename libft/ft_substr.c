/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 23:18:15 by jalease           #+#    #+#             */
/*   Updated: 2020/11/02 23:22:58 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (s != NULL && len >= 0)
	{
		if (start < ft_strlen(s) && (ptr = (char*)malloc(len + 1)) != NULL)
		{
			while (i < len)
			{
				ptr[i] = s[start + i];
				i++;
			}
			ptr[i] = '\0';
		}
		else if ((ptr = (char*)malloc(1)) != NULL)
			*ptr = '\0';
		return (ptr);
	}
	else if ((ptr = (char*)malloc(1)) != NULL)
		*ptr = '\0';
	return (NULL);
}
