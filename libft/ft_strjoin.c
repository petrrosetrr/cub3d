/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:12:34 by jalease           #+#    #+#             */
/*   Updated: 2020/11/02 13:29:22 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((ptr = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)) != NULL)
	{
		while (s1[j] != '\0')
		{
			ptr[i++] = s1[j++];
		}
		j = 0;
		while (s2[j] != '\0')
		{
			ptr[i++] = s2[j++];
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (NULL);
}
