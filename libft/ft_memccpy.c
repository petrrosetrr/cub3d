/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:49:14 by jalease           #+#    #+#             */
/*   Updated: 2020/10/31 22:20:21 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	size_t	i;

	if (destination == NULL && source == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		*((unsigned char*)destination + i) = *((unsigned char*)source + i);
		if (*((unsigned char*)source + i) == (unsigned char)c)
			return ((unsigned char*)(destination + i + 1));
		i++;
	}
	return (NULL);
}
