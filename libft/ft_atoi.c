/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:25:46 by jalease           #+#    #+#             */
/*   Updated: 2020/11/01 22:35:07 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	int			s;
	long int	res;
	int			i;

	i = 0;
	res = 0;
	s = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str++ - '0';
		i++;
		if (i > 19 && s == -1)
			return (0);
		if (i > 19 && s == 1)
			return (-1);
	}
	return (res * s);
}
