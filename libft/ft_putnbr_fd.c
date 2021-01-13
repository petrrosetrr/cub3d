/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:27:58 by jalease           #+#    #+#             */
/*   Updated: 2020/11/03 22:24:03 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char		arr[13];
	size_t		i;
	long int	temp;

	temp = (long int)n;
	if (temp < 0)
	{
		temp = -1 * temp;
		write(fd, "-", 1);
	}
	if (temp == 0)
		write(fd, "0", 1);
	i = 0;
	while (temp > 0)
	{
		arr[i] = 48 + temp % 10;
		temp = temp / 10;
		i++;
	}
	while (i > 0 && n != 0)
	{
		write(fd, arr + i - 1, 1);
		i--;
	}
}
