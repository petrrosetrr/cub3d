/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:09:57 by jalease           #+#    #+#             */
/*   Updated: 2020/11/01 12:51:23 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;

	if (dst != NULL && src != NULL)
	{
		src_len = ft_strlen(src);
		if (src_len < dstsize)
		{
			ft_memmove(dst, src, src_len + 1);
		}
		else if (dstsize > 0)
		{
			ft_memmove(dst, src, dstsize - 1);
			*(dst + (dstsize - 1)) = '\0';
		}
		return (ft_strlen(src));
	}
	return (0);
}
