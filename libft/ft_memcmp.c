/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:14:57 by jalease           #+#    #+#             */
/*   Updated: 2020/11/01 18:51:03 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		s1_temp;
	int		s2_temp;

	i = 0;
	while (n--)
	{
		s1_temp = (int)*((unsigned char*)s1 + i);
		s2_temp = (int)*((unsigned char*)s2 + i);
		if (s1_temp - s2_temp)
		{
			return (s1_temp - s2_temp);
		}
		i++;
	}
	return (0);
}
