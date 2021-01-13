/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 22:49:42 by jalease           #+#    #+#             */
/*   Updated: 2020/11/02 22:52:55 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if ((ptr = (char*)malloc(ft_strlen(s1) + 1)) != NULL)
	{
		while (*s1 != 0)
		{
			ptr[i] = *s1++;
			i++;
		}
		ptr[i] = *s1;
		return (ptr);
	}
	return (NULL);
}
