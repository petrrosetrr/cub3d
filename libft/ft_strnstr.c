/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:26:20 by jalease           #+#    #+#             */
/*   Updated: 2020/11/02 17:04:40 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	if (ft_strlen(needle) == 0)
		return ((char*)haystack);
	i = 0;
	while (i < len && i < ft_strlen(haystack))
	{
		j = 0;
		while (needle[j] != 0 && i + j < len)
		{
			if (needle[j] != haystack[j + i])
				break ;
			if (needle[j + 1] == 0)
				return ((char*)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
