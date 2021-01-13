/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:18:58 by jalease           #+#    #+#             */
/*   Updated: 2020/10/31 21:04:09 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t	i;

	if (destination == NULL && source == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		*((char*)destination + i) = *((char*)source + i);
		i++;
	}
	return (destination);
}
