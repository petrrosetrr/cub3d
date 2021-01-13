/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:46:50 by jalease           #+#    #+#             */
/*   Updated: 2020/10/29 14:42:42 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	i;
	char	*arr;

	arr = (char *)destination;
	i = 0;
	while (i < n)
	{
		arr[i] = c;
		i++;
	}
	return (arr);
}
