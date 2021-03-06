/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:17:10 by jalease           #+#    #+#             */
/*   Updated: 2020/11/02 22:53:58 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i] != 0)
	{
		i++;
	}
	while (&s[i] != s - 1)
	{
		if (s[i] == c)
		{
			return ((char*)(s + i));
		}
		i--;
	}
	return (NULL);
}
