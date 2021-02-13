/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 06:00:04 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 06:13:02 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "ft_validation.h"

static void	init_struct(t_cz *f, char *prev, char *this, char *next)
{
	f->str = "012NSWE";
	f->length[0] = ft_strlen(prev) - 1;
	f->length[1] = ft_strlen(this) - 1;
	f->length[2] = ft_strlen(next) - 1;
	f->prev = prev;
	f->this = this;
	f->next = next;
}

int			check_zero2(t_cz *f, int i)
{
	if (i == f->length[1] - 1)
	{
		if (f->prev[i + 1] != '1' ||
				f->this[i + 1] != '1' || f->next[i + 1] != '1')
			return (0);
	}
	else if (i == 1)
	{
		if (f->prev[i - 1] != '1' || f->this[i - 1] != '1'
		|| f->next[i - 1] != '1')
			return (0);
	}
	if (!(ft_strchr(f->str, f->prev[i - 1]) && ft_strchr(f->str, f->prev[i])
	&& ft_strchr(f->str, f->prev[i + 1])))
		return (0);
	if (!(ft_strchr(f->str, f->next[i - 1]) && ft_strchr(f->str, f->next[i])
	&& ft_strchr(f->str, f->next[i + 1])))
		return (0);
	return (1);
}

int			check_zero(int i, char *prev, char *this, char *next)
{
	t_cz f;

	init_struct(&f, prev, this, next);
	if (i == 0 || f.length[1] == i)
		return (0);
	if (ft_strchr(f.str, this[i - 1]) != NULL
		&& ft_strchr(f.str, this[i + 1]) != NULL)
	{
		if (f.length[0] > i && f.length[2] > i)
		{
			if (!check_zero2(&f, i))
				return (0);
		}
		else
			return (0);
		return (1);
	}
	return (0);
}
