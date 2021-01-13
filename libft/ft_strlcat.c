/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:58:56 by jalease           #+#    #+#             */
/*   Updated: 2020/11/01 19:36:47 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t dst_len;

	src_len = ft_strlen(src);
	if ((dst_len = ft_strlen(dst)) > dstsize)
	{
		dst_len = dstsize;
		return (dst_len + src_len);
	}
	dst += dst_len;
	while (dstsize - dst_len > 1 && *src != 0)
	{
		*dst++ = *src++;
		dstsize--;
	}
	*dst = '\0';
	return (dst_len + src_len);
}
