/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:56:32 by jalease           #+#    #+#             */
/*   Updated: 2020/11/02 20:04:52 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	size_t	i;

	if (destination == NULL && source == NULL)
		return (NULL);
	i = 0;
	if (destination < source)
	{
		while (i < n)
		{
			*((char*)destination + i) = *((char*)source + i);
			i++;
		}
	}
	else
	{
		while (n--)
		{
			*((char*)destination + n) = *((char*)source + n);
		}
	}
	return (destination);
}
